/* cttp_server.c
 *
 * Contains the main public wrapper to start the HTTP 1.1 server as well as
 * other functions to help the server run. This is the main entry point for
 * the server itself, and it will call other functions and other modules
 * to help respond to requests and dispatch files
 *
 * Functions:
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "request_parse.h"
#include "return_codes.h"
#include "file_dispatch.h"
#include "http_response.h"
#include "cttp_server.h"

/****** private constants ******/

// buffer size allocated for reading network requests. At 64k for now
const unsigned int REQ_BUF_SIZE = 64000;

/****** private struct definitions ******/

// used as s return type so function can return a file descriptor as well as a
// sockaddr_in struct ptr
struct socket_sockfd {
    struct sockaddr_in *sa_ptr;
    int sockfd;
};

// For historical reasons, the signal handling callback function cannot accept
// any parameters, so we need to store some data in a static struct
// stat = 0 while running, 1 if we need to stop
struct cttp_server_vars {
    sig_atomic_t stat;
    int client_sock;
};

/****** private globals ******/

static struct cttp_server_vars server;

/****** private function prototypes ******/

static void sig_handler(int signum);
static int bind_addr(int port);
static bool unbind_addr(int sock_fd);
static char *ip_addr_str(struct sockaddr_in *addr);
static char *network_request_string(int sockfd);

/****** private function definitions ******/

/* takes care of closing the program if there is an interrupt
 */
static void sig_handler(int signum)
{
    close(server.client_sock);
    server.stat = 1;
}

/* Attempts to unbind a socket to terminate a connection
 */
static bool unbind_addr(int sock_fd)
{
    return (close(sock_fd) == 0);
}

/* Binds a socket for the server so it can listen for and accept TCP
 * connections. Will return -1 if there is an error/if it fails to
 * bind. On success, will return a socket file descriptor.
 */
static int bind_addr(int port)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    struct socket_sockfd ret;

    // failed to open socket
    if (sock_fd < 0) {
        fprintf(stderr, "failed to open socket\n");
        return -1;
    }

    // setting socket settings
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // if < 0, then socket failed to bind
    if (bind(sock_fd, (struct sockaddr*) &server_addr,
                sizeof(server_addr)) < 0) {
        fprintf(stderr, "socket failed to bind\n");
        return -1;
    } else {
        return sock_fd;
    }
}

/* returns a nicely formatted string indicating which address the sockaddr_in
 * structure is bound to. Will return NULL on error. Otherwise returns a nicely
 * formatted string. This string is malloc'd and will have to be freed.
 */
static char *ip_addr_str(struct sockaddr_in *addr)
{
    char *ip_str = NULL;

    // determining whether socket address is IPv4 or IPv6
    switch(addr->sin_family) {
        case AF_INET: {
                          struct sockaddr_in *addr_in = (struct sockaddr_in *) addr;
                          ip_str = malloc(INET_ADDRSTRLEN);
                          inet_ntop(AF_INET, &(addr_in->sin_addr), ip_str, INET_ADDRSTRLEN);
                          break;
                      }
        case AF_INET6:
                      {
                          struct sockaddr_in6 *addr_in6 = (struct sockaddr_in6 *) addr;
                          ip_str = malloc(INET6_ADDRSTRLEN);
                          inet_ntop(AF_INET6, &(addr_in6->sin6_addr), ip_str, INET6_ADDRSTRLEN);
                          break;
                      }
        default:
                      break;
    }

    return ip_str;
}

/* Given a valid socket file descriptor, listens and waits for a network
 * request. For a valid request, the function will return a newly allocated
 * string. If there is an error or if the socket file descriptor is invalid,
 * it will return NULL. The returned string must be freed unless it is NULL.
 */
static char *network_request_str(int sock_fd)
{
    // invalid socket file descriptor
    if (sock_fd < 0)
        return NULL;

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    listen(sock_fd, 5);  // start listening

    if (server.stat != 0)
        return NULL;

    // 64K buffer for reading network request
    // Allocating this down here because if program is terminated beforehand,
    // we don't need to allocate it at all
    char *buf = calloc(REQ_BUF_SIZE, sizeof(char));
    int incoming_sock_fd = accept(sock_fd, (struct sockaddr *) &client_addr,
            &client_len);

    if (incoming_sock_fd < 0 || server.stat != 0) {
        free(buf);
        fprintf(stderr, "error accepting socket\n");
        return NULL;
    }

    // Set global so that the socket can be closed outside of this function
    // on SIGTERM or after writing a response
    server.client_sock = incoming_sock_fd;

    // Otherwise, read into buffer
    int n = read(incoming_sock_fd, buf, REQ_BUF_SIZE-1);

    // if we were able to read, return the string, otherwise free the buffer
    // and return NULL, indicating an error
    if (n >= 0) {
        return buf;
    } else {
        free(buf);
        return NULL;
    }
}

/****** public function definitions ******/

/* Starts the CTTP server and runs all necessary dispatch functions to respond
 * to requests and dispatch files. Returns an exit code indicating whether the
 * server ran correctly or exited due to an error.
 */
int cttp_server_run(int port, const char *root)
{
    // signal handling so this can be interrupted
    server.stat = 0;
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);

    // Start by binding to a TCP port and listening for connections
    int server_sock_fd = bind_addr(port);

    // terminate if we could not bind to the socket
    if (server_sock_fd < 0)
        return RET_NET_ERROR;

    // Listen for incoming connections
    // TODO, spawn new thread for each network request
    while (server.stat == 0) {
        char *req = network_request_str(server_sock_fd);

        // NULL indicates error reading request
        if (req != NULL) {
            char *base_path = get_req_path(GET, req);

            if (base_path == NULL)
                break;

            // find the file if it's valid, then serve it as a response
            // concatenate base path with new path
            char *full_fp_str = calloc(strlen(root) + strlen(base_path) + 2, sizeof(char));
            strcpy(full_fp_str, root);
            strcat(full_fp_str, base_path);

            if (full_fp_str == NULL)
                break;

            printf("File \"%s\" requested...\n", full_fp_str);
            char *resp = create_http_response(full_fp_str);

            // if we have a valid response, send it to the client
            if (resp != NULL) {
                printf("...File sent\n");
                write(server.client_sock, resp, strlen(resp) + 1);
                free(resp);
            }

            close(server.client_sock);
            free(base_path);
            free(req);
        }
    }

    if (unbind_addr(server_sock_fd)) {
        return 0;
    } else {
        return RET_NET_ERROR;
    }
}

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
#include "cttp_server.h"

/****** private constants ******/

// buffer size allocated for reading network requests
const unsigned int REQ_BUF_SIZE = 64000;

/****** private struct definitions ******/

// used as s return type so function can return a file descriptor as well as a
// sockaddr_in struct ptr
struct socket_sockfd {
    struct sockaddr_in *sa_ptr;
    int sockfd;
};

/****** private function prototypes ******/

static int bind_addr(int port);
static bool unbind_addr(struct socket_sockfd *server_addr);
static char *ip_addr_str(struct sockaddr_in *addr);
static char *network_request_string(int sockfd);

/****** private function definitions ******/

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
        // TODO return some sort of error
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
        // TODO print error that socket failed to bind
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

    // 64K buffer for reading network request
    char *buf = calloc(REQ_BUF_SIZE, sizeof(char));
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    listen(sock_fd, 5);  // start listening

    int incoming_sock_fd = accept(sock_fd, (struct sockaddr *) &client_addr,
            &client_len);

    // Check that the incoming socket was accepted correctly
    if (incoming_sock_fd < 0) {
        fprintf(stderr, "error accepting socket\n");
        return NULL;
    }

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
    // Start by binding to a TCP port and listening for connections
    int server_sock_fd = bind_addr(port);

    // Listen for incoming connections
    // TODO, spawn new thread for each network request
    for (;;) {
        char *req = network_request_str(server_sock_fd);

        // NULL indicates error reading request
        if (req != NULL) {
            printf("network request received:\n\n%s", req);
            free(req);
        }
    }
    return 0;
}

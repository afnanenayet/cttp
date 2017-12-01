/* cttp.c   Afnan Enayet
 *
 * The main file for the cttp program. It contains the main function and logic
 * for the dispatch of cttp
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cttp_server.h"

/****** constants ******/
const int DEF_PORT = 8080;

/****** function prototypes ******/

static bool arg_check(int argc, char *argv[]);
static void print_usage();
static int str_to_port(char *port_str);

/****** function definitions ******/

int main(int argc, char *argv[])
{
    bool run = arg_check(argc, argv);

    // If arguments are invalid, print proper usage and exit
    // otherwise start main program
    if (!run) {
        print_usage();
        return 1;
    } else {
        int port = str_to_port(argv[2]);

        // with error, set to default port value
        if (port == -1)
            port = DEF_PORT;

        cttp_server_run(port, NULL);
    }

    return 0;
}

/* Checks the arguments to see if they are valid or not. If they are, the
 * function will return true. It will also print error messages as
 * necessary to stdout/stderr indicating which arguments are invalid
 */
static bool arg_check(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "not enough arguments given\n");
        return false;
    } else {
        // see if we can convert port str to integer, if it is not a valid
        // number, this is an error
        return str_to_port(argv[2]) != -1;
    }
}

/* Prints instructions on how to use the program to STDOUT
*/
static void print_usage()
{
    printf("usage: cttp [base path] [port (optional, "
            "default: 80)]\n");
}

/* given a string representing the port, returns the representation 
 * of the port or returns -1 if the string is not parseable
 */
static int str_to_port(char *port_str)
{
    // Convert port to long
    errno = 0;
    char *endptr;
    long port = strtol(port_str, &endptr, 10);

    // If no error, return port. Otherwise return -1 as an error code
    if (errno == 0) {
        return (int) port;
    } else {
        return -1;
    }
}

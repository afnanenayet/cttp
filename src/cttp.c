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
#include "file_dispatch.h"

/****** constants ******/

const int DEF_PORT = 8080;

/****** private function prototypes ******/

static int arg_check(int argc, char *argv[]);
static void print_usage();
static int str_to_port(char *port_str);

/****** public function definitions ******/

int main(int argc, char *argv[])
{
    // return code from argument check, cttp server
    int ret_code = arg_check(argc, argv);

    // If arguments are invalid, print proper usage and exit
    // otherwise start main program
    if (ret_code != 0) {
        print_usage();
        return ret_code;
    } else {
        int port = DEF_PORT;

        // set port to supplied port per user's request
        if (argc > 2)
            port = str_to_port(argv[2]);

        // with error, set to default port value
        if (port == -1)
            port = DEF_PORT;
        ret_code = cttp_server_run(port, argv[1]);
    }
    return ret_code;
}

/****** private function definitions ******/

/* Checks the arguments to see if they are valid or not. If they are, the
 * function will return true. It will also print error messages as
 * necessary to stdout/stderr indicating which arguments are invalid
 *
 * Will return an error code that corresponds to the argument given.
 * - 0: arguments ok
 * - 1: not enough arguments supplied
 * - 2: invalid port number
 * - 3: invalid base path supplied
 */
static int arg_check(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "not enough arguments given\n");
        return 1;
    } else if (!is_valid_dir(argv[1])) {
        fprintf(stderr, "supplied base path is not a valid directory\n");
        return 3;
    } else if (argc >= 3) {
        // see if we can convert port str to integer, if it is not a valid
        // number, this is an error
        int port = str_to_port(argv[2]) != -1;

        if (port == -1) {
            fprintf(stderr, "invalid port provided\n");
            return 2;
        } else
            return 0;
    } else {
        return 0;
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

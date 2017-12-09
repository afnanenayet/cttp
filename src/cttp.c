/* cttp.c   Afnan Enayet
 *
 * The main file for the cttp program. It contains the main function and logic
 * for the dispatch of cttp
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> // getopt
#include "return_codes.h"
#include "cttp_server.h"
#include "file_dispatch.h"
#include "arg_util.h"

/****** constants ******/

const int DEF_PORT = 8080;

/****** private function prototypes ******/
static void print_usage();

/****** public function definitions ******/

int main(int argc, char *argv[])
{
    // arguments will live here so that they can be passed around as a
    // bundle as necessary
    cttp_args args;
    int ret_code;
    extract_args(argc, argv, &args);

    // If arguments are invalid, print proper usage and exit
    // otherwise start main program
    if (verify_args(&args)) {
        ret_code = cttp_server_run(args.port, args.dir);
        return ret_code;
    } else {
        print_usage();
        return RET_ARG_ERROR;
    }
    return ret_code;
}

/****** private function definitions ******/

/* Prints instructions on how to use the program to STDOUT
*/
static void print_usage()
{
    printf("usage: cttp -r [base path] -p [port (optional, "
            "default: 8080)]\n");
}

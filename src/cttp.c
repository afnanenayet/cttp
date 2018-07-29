/* cttp.c   Afnan Enayet
 *
 * The main file for the cttp program. It contains the main function and logic
 * for the dispatch of cttp
 */

#include "arg_util.h"
#include "cttp_server.h"
#include "file_dispatch.h"
#include "return_codes.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// getopt
#include <unistd.h>

/****** constants ******/

const int DEF_PORT = 8080;

/****** private function prototypes ******/

static void
print_usage();

/****** public function definitions ******/

int
main(int argc, char* argv[])
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
  } else {
    print_usage();
    ret_code = RET_ARG_ERROR;
  }
  return ret_code;
}

/****** private function definitions ******/

/* Prints instructions on how to use the program to STDOUT
 */
static void
print_usage()
{
  printf("usage: cttp -r [base path] -p [port (optional, "
         "default: %d)]\n",
         DEF_PORT);
}

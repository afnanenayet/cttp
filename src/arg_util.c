/* arg_util.c
 *
 * A set of helper functions designed to help with parsing/extracting
 * arguments and verifying them.
 *
 * Functions:
 *   - extract_args: extracts arguments from the command line and attempts to
 *     convert them to their proper types
 *   - verify_args: verifies that the arguments are valid
 *   - str_to_port: given a string, attempts to convert it to an integer
 *       representing a port
 */

#include "arg_util.h"
#include "file_dispatch.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h> // getopt

/****** private function prorotypes ******/

static int
str_to_port(char* port_str);

/****** public function definitions ******/

/* Given the system args, extract information into a provided cttp_args struct
 * Note that this function does not allocate a struct and that the user must
 * do this themselves. This function uses the getopt library to extract the
 * arguments.
 */
void
extract_args(int argc, char* argv[], cttp_args* args)
{
  // set defaults for args, so if something is missing, dir/port will appear
  // invalid
  args->dir = NULL;
  args->port = 8080;

  opterr = 0; // need to reset this just in case optarg had errors anywhere else
  char* OPTS = "r:p:";
  int opt = 0;

  // loop through commands while they're there
  while ((opt = getopt(argc, argv, OPTS)) != -1)
    switch (opt) {
      case 'r':
        args->dir = optarg;
        break;
      case 'p':
        // if str_to_port fails, the port will be -1
        args->port = str_to_port(optarg);
        break;
    }
  opterr = 0;
}

/* Given a cttp_args struct, verifies the data, returning a boolean value
 * indicating whether the arguments are valid. Checks to see if port is a
 * valid port number, and if the root path supplied for the HTTP server
 * is accessible and a valid directory.
 */
bool
verify_args(cttp_args* args)
{
  // check validity of the port
  if (args->port <= -1 || !is_valid_dir(args->dir))
    return false;
  else
    return true;
}

/****** private function definitions ******/

/* given a string representing the port, returns the representation
 * of the port or returns -1 if the string is not parseable. If
 * the port str is null or if there is an error, the function will
 * return NULL.
 */
static int
str_to_port(char* port_str)
{
  if (port_str == NULL)
    return -1;

  // Convert port to long
  errno = 0;
  char* endptr;
  long port = strtol(port_str, &endptr, 10);

  // If no error, return port. Otherwise return -1 as an error code
  if (errno == 0) {
    return (int)port;
  } else {
    return -1;
  }
}

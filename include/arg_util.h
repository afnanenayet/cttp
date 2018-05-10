#ifndef _ARG_UTIL_H
#define _ARG_UTIL_H

/****** public struct prototypes ******/

typedef struct cttp_args
{
  char* dir;
  int port;
} cttp_args;

/****** public function prototypes ******/

/* Given the system args, extract information into a provided cttp_args struct
 * Note that this function does not allocate a struct and that the user must
 * do this themselves. This function uses the getopt library to extract the
 * arguments.
 */
void
extract_args(int argc, char* argv[], cttp_args* args);

/* Given a cttp_args struct, verifies the data, returning a boolean value
 * indicating whether the arguments are valid. Checks to see if port is a
 * valid port number, and if the root path supplied for the HTTP server
 * is accessible and a valid directory.
 */
bool
verify_args(cttp_args* args);

#endif // _ARG_UTIL_H

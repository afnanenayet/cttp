/* file_dispatch.h
 *
 * This module contains helper functions related to file dispatching/
 * distribution as necessary for the HTTP server.
 */

#ifndef _FILE_DISPATCH_H
#define _FILE_DISPATCH_H

#include <stdbool.h>

/* Returns a boolean value indicating whether a given directory name is a
 * valid directory. This will return false if the input is null, isn't a valid
 * directory, or cannot be accessed for some reason.
 *
 * Typical usage: used to determine whether the file or requested exists from
 * an HTTP request. Also used to verify the base path from the command line
 * arguments.
 */
bool is_valid_dir(char *dirname);

#endif  // _FILE_DISPATCH_H

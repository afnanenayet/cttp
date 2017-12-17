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

/* Returns a boolean value indicating whether a given file path points to a
 * valid file. Will return false if the filepath is NULL, if the file path
 * does not point to an actual file, or if the file cannot be accessed for any
 * reason.
 */
bool is_valid_file(char *filepath);

/* Will attempt to read a text file and return a string with the file's
 * contents. Will return NULL if the file path is not valid or if any
 * errors occur trying to read the file. The file string is malloc'd and
 * will have to be freed.
 */
char *read_file_to_str(char *filepath);

/* retrieves the MIME-type from a file path string (simply checks the
 * extension in the file path string). The string returned here is static
 * and IS NOT allocated, and thus will not need to be freed. Will return
 * NULL if the string is not a valid file extension (e.g. a file extension
 * that's supposrted by the server).
 */
const char *get_mime_from_file(char *fp_str);

#endif  // _FILE_DISPATCH_H

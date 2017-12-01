/* file_dispatch.c
 *
 * A module with helper functions related to finding and serving files and
 * directories.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file_dispatch.h"

/* Returns a boolean value indicating whether a given directory name is a
 * valid directory. This will return false if the input is null, isn't a valid
 * directory, or cannot be accessed for some reason.
 *
 * Typical usage: used to determine whether the file or requested exists from
 * an HTTP request. Also used to verify the base path from the command line
 * arguments.
 */
bool is_valid_dir(char *dirname)
{
    struct stat path_stat;
    stat(dirname, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

/* Returns a boolean value indicating whether a given file path points to a
 * valid file. Will return false if the filepath is NULL, if the file path
 * does not point to an actual file, or if the file cannot be accessed for any
 * reason.
 */
bool is_valid_file(char *filepath)
{
    struct stat path_stat;
    stat(filepath, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

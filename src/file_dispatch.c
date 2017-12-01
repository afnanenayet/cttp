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

/* Will attempt to read a text file and return a string with the file's
 * contents. Will return NULL if the file path is not valid or if any
 * errors occur trying to read the file. The file string is malloc'd and
 * will have to be freed.
 */
char *read_file_to_str(char *filepath)
{
    // if it's not a valid file, don't bother reading it
    if (!is_valid_file(filepath))
        return NULL;

    FILE *fp = fopen(filepath, "rb");

    // getting length of the file so we know how much memory to allocate
    fseek(filepath, 0, SEEK_END);
    size_t file_size = ftell(filepath);
    rewind(input_file); // rewind to read from the beginning

    // read file into allocated buffer
    char *file_str = calloc(file_size, sizeof(char));
    fread(file_str, sizeof(char), file_size, filepath);
    close(fp);
    return file_str;
}

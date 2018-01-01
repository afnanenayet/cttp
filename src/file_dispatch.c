/* file_dispatch.c
 *
 * A module with helper functions related to finding and serving files and
 * directories.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "mime_types.h"
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
    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);
    rewind(fp); // rewind to read from the beginning

    // read file into allocated buffer
    char *file_str = calloc(file_size + 1, sizeof(char));
    fread(file_str, sizeof(char), file_size, fp);
    fclose(fp);
    return file_str;
}

/* retrieves the MIME-type from a file path string (simply checks the
 * extension in the file path string). The string returned here is static
 * and IS NOT allocated, and thus will not need to be freed. Will return
 * NULL if the string is not a valid file extension (e.g. a file extension
 * that's supported by the server).
 */
const char *get_mime_from_file(char *fp_str)
{
    if (fp_str == NULL)
        return NULL;

    char *delim = ".";
    char *tok;

    // copying the string because strtok is destructive
    char *fp_copy = calloc(strlen(fp_str) + 1, sizeof(char));
    strcpy(fp_copy, fp_str);
    char *next = strtok(fp_copy, delim);

    // no extension in file path
    if (next == NULL) {
        free(fp_copy);
        return NULL;
    }

    // loop through ever "." in the string and see if it has a match in
    // the MIME helper. This should leave us with the last extension
    while (next != NULL) {
        tok = next;
        next = strtok(NULL, delim);
    }
    const char *mime = ext_to_mime(tok);
    free(fp_copy);
    return mime;
}

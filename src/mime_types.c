/* mime_types.c
 *
 * A set of functions that helps convert between extension strings and mime
 * type strings.
 *
 * Functions:
 * - ext_to_mime: returns a mime type string that corresponds to a given
 *   extension
 *
 * - mime_to_ext: returns an extension that corresponds to a given MIME type
 *   string
 */

#include "mime_types.h"
#include <string.h> // using string instead of strings for portability

/****** public variables ******/

const char *MIME[] = {
    ".html", "text/html",       ".htm", "text/html",     ".css", "text/css",
    ".gif",  "image/gif",       ".png", "image/png",     ".jpg", "image/jpeg",
    ".xml",  "application/xml", ".svg", "image/svg+xml", ".txt", "text/plain",
    NULL // terminating NULL so we don't have to keep track of array size
};

/******* public function definitions ******/

/* Retrieves the MIME type string given an extension. Will only work on
 * extensions present in the MIME array/for MIME types that are supported
 * by the server. Will return NULL if the extension is invalid or
 * unsupported.
 *
 * ext: the extension string (e.g. ".html", ".css", etc)
 *
 * returns: a mime type string (e.g. ".html" -> "text/html"
 */
const char *ext_to_mime(char *ext) {
    if (ext == NULL)
        return NULL;

    // search for the extension in the array
    // the format of the array is extension, mime string, so the corresponding
    // MIME type for an extension is at index i + 1 if the extension is at
    // index i
    int i = 0;
    for (; MIME[i] != NULL && !strcmp(MIME[i], ext); i++) {
    }

    // need to make sure that the string is valid/in the array and that the
    // given string is an extension
    if (strcmp(MIME[i], ext) && i % 2 == 0) {
        return MIME[i + 1];
    } else {
        return NULL;
    }
}

/* Retrieves the extension given a MIME type string. This only applies for the
 * MIME types present in the MIME array defined above, which are the MIME types
 * that the server support. Will return NULL if the MIME type is invalid or
 * unsupported.
 *
 * mime_type: the mime type string (e.g. "text/html")
 *
 * returns: the extension string
 */
const char *mime_to_ext(char *mime_type) {
    if (mime_type == NULL)
        return NULL;

    // Searching for the index of the mime type string in the array
    int i = 0;
    for (; MIME[i] != NULL && !strcmp(MIME[i], mime_type); i++) {
    }

    // need to make sure string is valid/in the array and a MIME type
    // The extension precedes the mime type in the array, which is why
    // we return the string at i-1
    // (mime types are in the odd indices)
    if (strcmp(MIME[i], mime_type) && i % 2 == 1) {
        return MIME[i - 1];
    } else {
        return NULL;
    }
}

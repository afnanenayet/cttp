/* mime_types.h
 *
 * A constant table that defines MIME types and their associated filenames
 * to help write headers so that browsers can parse data properly.
 *
 * Typical usage: find the file extension at position i, then get the MIME-type
 * at position i + 1
 *
 * Functions:
 *
 *   - ext_to_mime: returns a mime type string that corresponds to a given
 *    extension
 *   - mime_to_ext: returns an extension that corresponds to a given a mime
 *     type string
 */

#ifndef _mime_types_h
#define _mime_types_h

/****** static variables ******/

extern static const char *const MIME[];

/****** public function prototypes ******/

/* Retrieves the MIME type string given an extension. Will only work on
 * extensions present in the MIME array/for MIME types that are supported
 * by the server. Will return NULL if the extension is invalid or
 * unsupported.
 *
 * ext: the extension string (e.g. ".html", ".css", etc)
 *
 * returns: a mime type string (e.g. ".html" -> "text/html"
 */
char *ext_to_mime(char *ext);

/* Retrieves the extension given a MIME type string. This only applies for the
 * MIME types present in the MIME array defined above, which are the MIME types
 * that the server support. Will return NULL if the MIME type is invalid or
 * unsupported.
 *
 * mime_type: the mime type string (e.g. "text/html")
 *
 * returns: the extension string
 */
char *mime_to_ext(char *mime_type);

#endif // _mime_types_h

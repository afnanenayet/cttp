/* mime_types.h
 *
 * A constant table that defines MIME types and their associated filenames
 * to help write headers so that browsers can parse data properly.
 *
 * Typical usage: find the file extension at position i, then get the MIME-type
 * at position i + 1
 */

static const char *const MIME[] {
    ".html", "text/html",
    ".htm", "text/html",
    ".css", "text/css",
    ".gif", "image/gif",
    ".png", "image/png",
    ".jpg", "image/jpeg",
    ".xml", "application/xml",
    ".svg", "image/svg+xml",
    ".txt", "text/plain",
}

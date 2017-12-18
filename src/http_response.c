/* http_response.c
 *
 * A set of helper functions designed to help construct a valid HTTP response
 * to send to an HTTP client.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "file_dispatch.h"
#include "http_response.h"

/****** private function prototypes ******/

static char *concat_str_end(char *template, char *text);
static int num_digits(int num);

/****** private function definitions ******/

/* Takes a template string and adds text to the end of it
 * Ex: "hello, " (template) and "world" (text) will be applied as
 * follows: "hello, %s\r\n" and returned. This process allocates a
 * new string that must be freed by the caller. Will return NULL
 * on error.
 */
static char *concat_str_end(char *template, char *text)
{
    if (template == NULL || text == NULL)
        return NULL;

    char *terminator = "\r\n";
    char *res = malloc(strlen(template) + strlen(text) + strlen(terminator)
            + 3);
    strcpy(res, template);
    strcat(res, text);
    strcat(res, terminator);
    return res;
}

/* Returns the number of digits in a number
 */
static int num_digits(int num)
{
    if (num == 0)
        return 1;
    else
        return floor(log10(abs(num))) + 1;
}

/****** public function definitions ******/

/* Creates an HTTP response from a file path string. If the argument is
 * invalid, or if the file cannot be read, the function will return NULL.
 * Otherwise, the string return is dynamically allocated and will need to
 * be freed by the caller.
 */
char *create_http_response(char *fp_str)
{
    if (fp_str == NULL)
        return NULL;

    if (!is_valid_file(fp_str))
        return NULL;

    char *mime_str = (char*) get_mime_from_file(fp_str);

    // set default type to text
    if (mime_str == NULL)
        mime_str = "text/plain";

    // The constants/template for each line of the HTTP response
    char *header = "HTTP/1.1 200 OK \r\n";
    char *content_type = "Content-Type: ";
    char *content_len_prefix = "Content-Length: ";
    char *sep = "\r\n\r\n";

    // the HTTP response string to be returned
    char *resp;

    // get the string representation of the file, if the file is valid
    char *file_str = read_file_to_str(fp_str);

    if (file_str != NULL) {
        // concatenate the two strings (header and content)
        int content_len = strlen(file_str) + strlen(sep);
        int num_len = num_digits(content_len + 1);

        resp = malloc(sizeof(char) * (
                    strlen(header) +
                    strlen(content_type) +
                    strlen(mime_str) +
                    strlen(content_len_prefix) +
                    strlen(file_str) +
                    strlen(sep) +
                    strlen(sep) +
                    num_len + 1
                ));
        sprintf(resp, "%s%s%s\r\n%s%d%s%s%s", header, content_type, mime_str,
                content_len_prefix, content_len, sep, file_str, sep);
        free(file_str);
        return resp;
    } else {
        return NULL;
    }
}

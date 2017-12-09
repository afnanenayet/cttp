/* http_response.c
 *
 * A set of helper functions designed to help construct a valid HTTP response
 * to send to an HTTP client.
 */

#include <string.h>
#include "http_response.h"

/****** private function prototypes ******/

static char *concat_str_end(char *template, char *text);

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
        return NULL

    // The constants/template for each line of the HTTP response
    char *status = "HTTP/1.1 200 OK ";
    char *content_len = "Content-Length: ";
    char *content_type = "Content-Type: ";
    char *date = "Date: ";

    // the HTTP response string to be returned
    char *resp;

    // get the string representation of the file, if the file is valid
    char *file_str = read_file_to_str(fp_str);
}

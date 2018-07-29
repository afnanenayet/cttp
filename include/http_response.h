/* http_response.h
 *
 * A set of helper functions that create an HTTP response string
 */

#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

/* Creates an HTTP response from a file path string. If the argument is
 * invalid, or if the file cannot be read, the function will return NULL.
 * Otherwise, the string return is dynamically allocated and will need to
 * be freed by the caller.
 */
char*
create_http_response(char* fp_str);

#endif // _HTTP_RESPONSE_H

/* request_parse.h
 *
 * This module provides helper functions in order to parse an HTTP request
 */

#ifndef _REQUEST_PARSE_H
#define _REQUEST_PARSE_H

/****** public constants ******/

enum HTTP_TYPE
{
    GET,
    PUT,
    POST,
    ERROR
} http_type;

/****** public function prototypes ******/

/* given a string representing an HTTP request, this function returns the
 * type of that HTTP request. If there is an error in the function, or if the
 * input is invalid, the function will return HTTP_TYPE.ERROR
 */
enum HTTP_TYPE get_http_type(char *req);

/* Given the HTTP type of the request and a request string, this funciton
 * returns the file path that's being requested. If there is an error, or if
 * the input is invalid, this function will return NULL.
 *
 * Note that the returned string is allocated by the function and must be
 * freed by the user.
 */
char *get_req_path(enum HTTP_TYPE http_type, char *req);

#endif  // _REQUEST_PARSE_H

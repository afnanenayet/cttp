/* request_parse.c
 *
 * This module provides helper functions to helpe parse HTTP requests
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "request_parse.h"

/****** private constants ******/

char *DELIM = " ";

/****** public function definitions ******/

/* given a string representing an HTTP request, this function returns the
 * type of that HTTP request. If there is an error in the function, or if the
 * input is invalid, the function will return HTTP_TYPE.ERROR
 */
enum HTTP_TYPE get_http_type(char *req)
{
    // copy the string so we don't destroy the original string
    char *cpy = calloc(strlen(req), sizeof(char));
    strcpy(cpy, req);
    // save result here so we can free the string before returning result
    enum HTTP_TYPE ret; 

    char *tok = strtok(DELIM, cpy);

    // Make sure that there is at least one instance of a ' '
    if (tok == NULL)
        ret = ERROR;

    // the http request type is the first word in the request string
    if (strcmp(tok, "GET")) {
        ret = GET;
    } else if (strcmp(tok, "PUT")) {
        ret = PUT;
    } else if (strcmp(tok, "POST")) {
        ret = POST;
    } else {
        ret = ERROR;
    }

    free(cpy);
    return ret;
}

/* Given the HTTP type of the request and a request string, this funciton
 * returns the file path that's being requested. If there is an error, or if
 * the input is invalid, this function will return NULL.
 *
 * Note that the returned string is allocated by the function and must be
 * freed by the user.
 */
char *get_req_path(enum HTTP_TYPE http_type, char *req)
{
    char *path = NULL; // the path to be returned to the user

    // This is a shim since this function doesn't support any other request
    // types :: TODO support other requests
    if (http_type == ERROR) {
        fprintf(stderr, "unsupported or invallid HTTP request type\n");
        return NULL;
    }

    // second token should be the path
    char *tok = strtok(req, DELIM);

    // just in case we get a faulty request
    if (tok != NULL)
        tok = strtok(NULL, DELIM);
    else
        return NULL;


    if (tok != NULL) {
        path = calloc(sizeof(char), strlen(tok));
        strcpy(path, tok);
        return path;
    } else {
        return NULL;
    }
}

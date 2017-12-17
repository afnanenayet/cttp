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

    char *tok = strtok(cpy, DELIM);

    // Make sure that there is at least one instance of a ' '
    if (tok == NULL)
        ret = ERROR;

    // the http request type is the first word in the request string
    if (strcmp(tok, "GET") == 0) {
        ret = GET;
    } else if (strcmp(tok, "PUT") == 0) {
        ret = PUT;
    } else if (strcmp(tok, "POST") == 0) {
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
    if (req == NULL)
        return NULL;

    // Must copy the request string because fn will modify the string
    // and we don't know if req is a string literal or not
    char *req_cpy = malloc(sizeof(char) * (strlen(req) + 1));
    strcpy(req_cpy, req);
    char *path = NULL; // the path to be returned to the user

    if (http_type == ERROR) {
        fprintf(stderr, "unsupported or invallid HTTP request type\n");
        return NULL;
    }

    // second token should be the path
    char *tok = strtok(req_cpy, DELIM);

    // just in case we get a faulty request
    if (tok != NULL)
        tok = strtok(NULL, DELIM);
    else {
        free(req_cpy);
        return NULL;
    }


    if (tok != NULL) {
        path = calloc(strlen(tok) + 1, sizeof(char));
        strcpy(path, tok);
        free(req_cpy);
        return path;
    } else {
        free(req_cpy);
        return NULL;
    }
}

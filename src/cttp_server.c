/* cttp_server.c
 *
 * Contains the main public wrapper to start the HTTP 1.1 server as well as
 * other functions to help the server run. This is the main entry point for
 * the server itself, and it will call other functions and other modules
 * to help respond to requests and dispatch files
 *
 * Functions:
 */

#include "cttp_server.h"

/****** private function prototypes ******/

static void bind_addr(const char *addr, int port);

/****** private function definitions ******/
static void bind_addr(const char *addr, int port) 
{
}

/****** public function definitions ******/

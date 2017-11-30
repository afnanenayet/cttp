/* cttp_server.h
 *
 * Functions for the main server process, including the main loop, dispatch
 * functions, socket binding, and content dispatch.
 */

#ifndef _cttp_server_h
#define _cttp_server_h

/* Starts the CTTP server and runs all necessary dispatch functions to respond
 * to requests and dispatch files
 */
int cttp_server_start(const char *addr, int port, const char *root);

#endif // _cttp_server_h

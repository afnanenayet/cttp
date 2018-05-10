/* cttp_server.h
 *
 * Functions for the main server process, including the main loop, dispatch
 * functions, socket binding, and content dispatch.
 */

#ifndef _cttp_server_h
#define _cttp_server_h

/****** public function prototypes ******/

/* Starts the CTTP server and runs all necessary dispatch functions to respond
 * to requests and dispatch files
 *
 * params:
 * - port: the port to serve from
 * - root: the name of the root directory to serve files from
 */
int
cttp_server_run(int port, const char* root);

#endif // _cttp_server_h

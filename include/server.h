/* server.h
 *
 * Functions for the main server process, including the main loop, dispatch
 * functions, socket binding, and content dispatch.
 */

#ifndef _server_h
#define _server_h

/* Binds the server to a certain address and port. Returns whether bind was
 * successful
 */
bool bind(const char *addr, int port);

/* main loop for HTTP server. Everything relevant to the server is dispatched
 * from here
 */
int main_loop();

#endif // _server_h

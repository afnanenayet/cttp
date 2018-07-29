/* return_codes.h
 *
 * Macros defining the return codes that the program can return
 */

#ifndef _RETURN_CODES_H
#define _RETURN_CODES_H

#define RET_OK (0)        // all systems ok
#define RET_ARG_ERROR (1) // generic argument error
#define RET_NET_ERROR (2) // networking error
#define RET_UNK_ERROR (3) // error unknown, probably SIGTERM

#endif // _RETURN_CODES_H

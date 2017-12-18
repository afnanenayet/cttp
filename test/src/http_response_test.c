
/* file_dispatch_test.c
 *
 * Testing file that corresponds to file_dispatch.h
 *
 * Tests all public functions from file dispatch to ensure that they are
 * working correctly.
 */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>
#include <cmocka.h>

#include "http_response.h"

void create_http_response_test() 
{
    // TODO
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(create_http_response_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

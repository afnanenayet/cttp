/* mime_types_test.c
 *
 * Unit tests that correspond to the functions found in mime_types.h
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

#include "mime_types.h"

// TODO...all of these tests lol
void ext_to_mime_test_valid_mimes()
{
}

void mime_to_ext_test_valid_exts()
{
}

void ext_to_mime_test_invalid_exts()
{
}

void mime_to_ext_test_invalid_mimes()
{
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(some_fn_ptr_here);
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

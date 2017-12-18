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

void ext_to_mime_test_valid_mimes()
{
    char *inputs[] = {
        "html",
        "svg",
        "gif",
        "txt",
        NULL,
    };

    char *expected[] = {
        "text/html",
        "image/svg+xml",
        "image/gif",
        "text/plain",
        NULL,
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        assert_string_equal(ext_to_mime(inputs[i]), expected[i]);
    }
}

void mime_to_ext_test_valid_exts()
{
    char *expected[] = {
        "html",
        "svg",
        "gif",
        "txt",
        NULL,
    };

    char *inputs[] = {
        "text/html",
        "image/svg+xml",
        "image/gif",
        "text/plain",
        NULL,
    };

    for (int i = 0; inputs[i] != NULL; i++) {
        assert_string_equal(mime_to_ext(inputs[i]), expected[i]);
    }
}

void ext_to_mime_test_invalid_exts()
{
    const int num_bad_inputs = 2;
    char *inputs[] = {
        "asdf;lkasdjf",
        NULL,
    };

    // Invalid inputs should all return NULL
    for (int i = 0; i < num_bad_inputs; i++) {
        assert_null(ext_to_mime(inputs[i]));
    }
}

void mime_to_ext_test_invalid_mimes()
{
    const int num_bad_inputs = 2;
    char *inputs[] = {
        "asdf;lkasdjf",
        NULL,
    };

    for (int i = 0; i < num_bad_inputs; i++) {
        assert_null(mime_to_ext(inputs[i]));
    }
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(ext_to_mime_test_valid_mimes),
        cmocka_unit_test(mime_to_ext_test_invalid_mimes),
        cmocka_unit_test(mime_to_ext_test_valid_exts),
        cmocka_unit_test(ext_to_mime_test_invalid_exts),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

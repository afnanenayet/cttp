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

#include "file_dispatch.h"

static void test_valid_dir()
{
    char *valid_dir = "/";
    assert_int_equal(is_valid_dir(valid_dir), true);
}

static void test_invalid_dir()
{
    char *invalid_dir = "thisisaninvaliddir";
    assert_int_equal(is_valid_dir(invalid_dir), false);

}

static void test_valid_file()
{
    // create a tmp file for testing
    char template[] = "XXXXXX";
    //
    // Create a temp file and store the filename in static_fname
    int temp_fd = mkstemp(template);
    assert_int_not_equal(temp_fd, -1);

    if (temp_fd != -1) {
        // record the results then clean up resources, run the assert
        int is_valid = is_valid_file(template);
        close(temp_fd);
        unlink(template);
        assert_int_equal(is_valid, true);
    }
}

static void test_invalid_file()
{
    char *invalid_file = "invalidfile.duh";
    assert_int_equal(is_valid_file(invalid_file), false);
}

static void test_read_file_to_str()
{
    // TODO
}

static void test_get_mime_from_file()
{
    char *inputs[] = {
        "/some/file/path/file.txt", // txt
        "some/file/path/file.html", // html
        "file.html", // html
        ".html",
    };

    char *bad_inputs[] = {
        "",
        ".badext",
        "some_file_with_no_ext",
        NULL,
    };

    char *expected[] = {
        "text/plain",
        "text/html",
        "text/html",
        "text/html",
    };

    const int num_good_in = 4; // the number of inputs
    const int num_bad_in = 4;

    for (int i = 0; i < num_good_in; i++) {
        assert_string_equal(get_mime_from_file(inputs[i]), expected[i]);
    }

    for (int i = 0; i < num_bad_in; i++) {
        assert_null(get_mime_from_file(bad_inputs[i]));
    }
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_valid_dir),
        cmocka_unit_test(test_invalid_dir),
        cmocka_unit_test(test_valid_file),
        cmocka_unit_test(test_invalid_file),
        cmocka_unit_test(test_read_file_to_str),
        cmocka_unit_test(test_get_mime_from_file),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

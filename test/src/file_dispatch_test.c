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

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_valid_dir),
        cmocka_unit_test(test_invalid_dir),
        cmocka_unit_test(test_valid_file),
        cmocka_unit_test(test_invalid_file),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

/* request_parse_test.c
 *
 * Unit tests for request_parse.c
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

#include "request_parse.h"

// TODO complete get_http_type tests
static void get_http_type_get_test()
{
    char *valid_get_inputs[] = {
        "GET / some data",
        "GET /",
        "GET ",
        NULL,
    };

    for (int i = 0; valid_get_inputs[i] != NULL; i++) {
        enum HTTP_TYPE ret_http_type;
        ret_http_type = get_http_type(valid_get_inputs[i]);
        assert_true(ret_http_type == GET);
    }
}

static void get_http_type_put_test()
{
    char *valid_get_inputs[] = {
        "PUT / some data",
        "PUT /",
        "PUT ",
        NULL,
    };

    for (int i = 0; valid_get_inputs[i] != NULL; i++) {
        enum HTTP_TYPE ret_http_type;
        ret_http_type = get_http_type(valid_get_inputs[i]);
        assert_true(ret_http_type == PUT);
    }
}

static void get_req_path_test()
{
    const int num_good_inputs = 3;

    // start with the good inputs because they are string comparisons
    char *inputs[] = {
        "GET /",
        "GET /usr/bin",
        "PUT hello",
    };

    char *expected[] = {
        "/",
        "/usr/bin",
        "hello",
    };

    for (int i = 0; i < num_good_inputs; i++) {
        char *path = get_req_path(GET, inputs[i]);
        assert_string_equal(path, expected[i]);
    }

    const int num_bad_inputs = 8;

    // bad inputs will throw NULL, which is a different macro
    char *bad_inputs[] = {
        "",
        NULL,
        "GET",
        "PUT",
        "/",
        "/usr/bin",
        "badinput",
        "GET ",
    };
    
    for (int i = 0; i < num_bad_inputs; i++) {
        assert_null(get_req_path(GET, bad_inputs[i]));
    }
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(get_http_type_get_test),
        cmocka_unit_test(get_http_type_put_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

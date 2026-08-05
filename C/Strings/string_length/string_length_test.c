#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "string_length.h"

#define TEST_PASS    (0)
#define TEST_FAIL    (1)

typedef struct
{
    const char *description;
    int (*function)(void);
} test_case_t;

static uint32_t total_tests = 0U;
static uint32_t passed_tests = 0U;

static void report_test(uint32_t current_test,
                        uint32_t planned_tests,
                        const char *description,
                        int result)
{
    ++total_tests;

    if (TEST_PASS == result)
    {
        ++passed_tests;
    }

    (void)printf("[%02u/%02u] %-30s [%s]\n",
                 current_test,
                 planned_tests,
                 description,
                 (TEST_PASS == result) ? "PASS" : "FAIL");

    (void)fflush(stdout);
}

static int test_empty_string(void)
{
    const char *str = "";
    uint32_t length = 0U;

    if (STR_STATUS_OK != string_length(str, &length))
    {
        return TEST_FAIL;
    }

    return (0U == length) ? TEST_PASS : TEST_FAIL;
}

static int test_normal_string(void)
{
    const char *str = "Embedded";
    uint32_t length = 0U;

    if (STR_STATUS_OK != string_length(str, &length))
    {
        return TEST_FAIL;
    }

    return (8U == length) ? TEST_PASS : TEST_FAIL;
}

static int test_string_with_space(void)
{
    const char *str = "Embedded Expert";
    uint32_t length = 0U;

    if (STR_STATUS_OK != string_length(str, &length))
    {
        return TEST_FAIL;
    }

    return (15U == length) ? TEST_PASS : TEST_FAIL;
}

static int test_single_character(void)
{
    const char *str = "A";
    uint32_t length = 0U;

    if (STR_STATUS_OK != string_length(str, &length))
    {
        return TEST_FAIL;
    }

    return (1U == length) ? TEST_PASS : TEST_FAIL;
}

static int test_null_string(void)
{
    uint32_t length = 0U;

    return (STR_STATUS_ERR_PARAM ==
            string_length(NULL, &length))
            ? TEST_PASS : TEST_FAIL;
}

static int test_null_output_pointer(void)
{
    const char *str = "Embedded";

    return (STR_STATUS_ERR_PARAM ==
            string_length(str, NULL))
            ? TEST_PASS : TEST_FAIL;
}

static const test_case_t test_cases[] =
{
    { "Empty string",              test_empty_string },
    { "Normal string",             test_normal_string },
    { "String with space",         test_string_with_space },
    { "Single character",          test_single_character },
    { "NULL string pointer",       test_null_string },
    { "NULL output pointer",       test_null_output_pointer }
};

int main(void)
{
    const uint32_t planned_tests =
        (uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));

    (void)printf("========================================\n");
    (void)printf("Running string_length unit tests\n");
    (void)printf("========================================\n");

    for (uint32_t i = 0U; i < planned_tests; ++i)
    {
        report_test(i + 1U,
                    planned_tests,
                    test_cases[i].description,
                    test_cases[i].function());
    }

    const uint32_t failed_tests = total_tests - passed_tests;

    (void)printf("----------------------------------------\n");
    (void)printf("Summary\n");
    (void)printf("----------------------------------------\n");

    (void)printf("Executed : %u/%u\n",
                 total_tests,
                 planned_tests);

    (void)printf("Passed   : %u/%u (%.0f%%)\n",
                 passed_tests,
                 planned_tests,
                 (100.0 * (double)passed_tests) / (double)planned_tests);

    (void)printf("Failed   : %u/%u (%.0f%%)\n",
                 failed_tests,
                 planned_tests,
                 (100.0 * (double)failed_tests) / (double)planned_tests);

    (void)printf("========================================\n");

    return (0U == failed_tests) ? EXIT_SUCCESS : EXIT_FAILURE;
}
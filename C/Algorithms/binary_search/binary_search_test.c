#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "binary_search.h"

#define TEST_PASS    (0)
#define TEST_FAIL    (1)

typedef struct
{
    const char *description;
    int (*function)(void);
} test_case_t;

static uint32_t total_tests  = 0U;
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

static int test_find_first_element(void)
{
    const uint32_t array[] = {10U, 20U, 30U, 40U, 50U};
    uint32_t index = 0U;

    if (SEARCH_STATUS_SUCCESS != binary_search(array,
                                          5U,
                                          10U,
                                          &index))
    {
        return TEST_FAIL;
    }

    return (0U == index) ? TEST_PASS : TEST_FAIL;
}

static int test_find_last_element(void)
{
    const uint32_t array[] = {10U, 20U, 30U, 40U, 50U};
    uint32_t index = 0U;

    if (SEARCH_STATUS_SUCCESS != binary_search(array,
                                          5U,
                                          50U,
                                          &index))
    {
        return TEST_FAIL;
    }

    return (4U == index) ? TEST_PASS : TEST_FAIL;
}

static int test_find_middle_element(void)
{
    const uint32_t array[] =
    {
        11U,22U,33U,44U,55U,66U,77U,88U
    };

    uint32_t index = 0U;

    if (SEARCH_STATUS_SUCCESS != binary_search(array,
                                          8U,
                                          55U,
                                          &index))
    {
        return TEST_FAIL;
    }

    return (4U == index) ? TEST_PASS : TEST_FAIL;
}

static int test_target_not_found(void)
{
    const uint32_t array[] =
    {
        10U,20U,30U,40U,50U
    };

    uint32_t index = 0U;

    return (SEARCH_STATUS_NOT_FOUND ==
            binary_search(array,
                          5U,
                          35U,
                          &index))
           ? TEST_PASS
           : TEST_FAIL;
}

static int test_null_pointer(void)
{
    uint32_t index = 0U;

    return (SEARCH_STATUS_INVALID_ARGUMENT  ==
            binary_search(NULL,
                          5U,
                          10U,
                          &index))
           ? TEST_PASS
           : TEST_FAIL;
}

static int test_zero_size(void)
{
    const uint32_t array[] =
    {
        10U
    };

    uint32_t index = 0U;

    return (SEARCH_STATUS_INVALID_ARGUMENT  ==
            binary_search(array,
                          0U,
                          10U,
                          &index))
           ? TEST_PASS
           : TEST_FAIL;
}

static int test_null_output_pointer(void)
{
    const uint32_t array[] =
    {
        10U,20U
    };

    return (SEARCH_STATUS_INVALID_ARGUMENT  ==
            binary_search(array,
                          2U,
                          20U,
                          NULL))
           ? TEST_PASS
           : TEST_FAIL;
}

static const test_case_t test_cases[] =
{
    { "Find first element",     test_find_first_element },
    { "Find last element",      test_find_last_element },
    { "Find middle element",    test_find_middle_element },
    { "Target not found",       test_target_not_found },
    { "NULL array pointer",     test_null_pointer },
    { "Zero array size",        test_zero_size },
    { "NULL output pointer",    test_null_output_pointer }
};

int main(void)
{
    const uint32_t planned_tests =
        (uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));

    (void)printf("========================================\n");
    (void)printf("Running binary_search unit tests\n");
    (void)printf("========================================\n");

    for (uint32_t i = 0U;
         i < planned_tests;
         ++i)
    {
        report_test(i + 1U,
                    planned_tests,
                    test_cases[i].description,
                    test_cases[i].function());
    }

    const uint32_t failed_tests =
        total_tests - passed_tests;

    (void)printf("----------------------------------------\n");
    (void)printf("Summary\n");
    (void)printf("----------------------------------------\n");

    (void)printf("Executed : %u/%u\n",
                 total_tests,
                 planned_tests);

    (void)printf("Passed   : %u/%u (%.0f%%)\n",
                 passed_tests,
                 planned_tests,
                 (100.0 * (double)passed_tests) /
                 (double)planned_tests);

    (void)printf("Failed   : %u/%u (%.0f%%)\n",
                 failed_tests,
                 planned_tests,
                 (100.0 * (double)failed_tests) /
                 (double)planned_tests);

    (void)printf("========================================\n");

    return (0U == failed_tests)
           ? EXIT_SUCCESS
           : EXIT_FAILURE;
}
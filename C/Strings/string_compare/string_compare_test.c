#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "string_compare.h"

#define TEST_CASE_COUNT (9U)

typedef struct
{
    const char *name;
    const char *lhs;
    const char *rhs;
    string_compare_status_t expected_status;
} test_case_t;

static uint32_t run_test(const test_case_t * const test_case,
                         const uint32_t test_number)
{
    const string_compare_status_t actual_status =
        string_compare(test_case->lhs,
                       test_case->rhs);

    if (actual_status == test_case->expected_status)
    {
        (void)printf("[%02u/%02u] %-28s [PASS]\n",
                     test_number,
                     TEST_CASE_COUNT,
                     test_case->name);

        return 1U;
    }

    (void)printf("[%02u/%02u] %-28s [FAIL]\n",
                 test_number,
                 TEST_CASE_COUNT,
                 test_case->name);

    (void)printf("         Expected: %u, Actual: %u\n",
                 (uint32_t)test_case->expected_status,
                 (uint32_t)actual_status);

    return 0U;
}

int main(void)
{
    static const test_case_t test_cases[] =
    {
        {
            "Equal strings",
            "hello",
            "hello",
            STRING_COMPARE_STATUS_EQUAL
        },
        {
            "Different strings",
            "hello",
            "world",
            STRING_COMPARE_STATUS_NOT_EQUAL
        },
        {
            "Different first character",
            "hello",
            "Hello",
            STRING_COMPARE_STATUS_NOT_EQUAL
        },
        {
            "Different last character",
            "hella",
            "hello",
            STRING_COMPARE_STATUS_NOT_EQUAL
        },
        {
            "Empty strings",
            "",
            "",
            STRING_COMPARE_STATUS_EQUAL
        },
        {
            "One empty string",
            "",
            "hello",
            STRING_COMPARE_STATUS_NOT_EQUAL
        },
        {
            "Same prefix different length",
            "hello",
            "hell",
            STRING_COMPARE_STATUS_NOT_EQUAL
        },
        {
            "Null first pointer",
            NULL,
            "hello",
            STRING_COMPARE_STATUS_INVALID_ARGUMENT
        },
        {
            "Null second pointer",
            "hello",
            NULL,
            STRING_COMPARE_STATUS_INVALID_ARGUMENT
        }
    };

    uint32_t index = 0U;
    uint32_t passed = 0U;

    (void)printf("========================================\n");
    (void)printf("Running string_compare unit tests\n");
    (void)printf("========================================\n");

    for (index = 0U; index < TEST_CASE_COUNT; ++index)
    {
        passed += run_test(&test_cases[index],
                           index + 1U);
    }

    (void)printf("----------------------------------------\n");
    (void)printf("Summary\n");
    (void)printf("----------------------------------------\n");

    (void)printf("Executed : %u/%u\n",
                 TEST_CASE_COUNT,
                 TEST_CASE_COUNT);

    (void)printf("Passed   : %u/%u (%.0f%%)\n",
                 passed,
                 TEST_CASE_COUNT,
                 (100.0 * (double)passed) /
                 (double)TEST_CASE_COUNT);

    (void)printf("Failed   : %u/%u (%.0f%%)\n",
                 TEST_CASE_COUNT - passed,
                 TEST_CASE_COUNT,
                 (100.0 * (double)(TEST_CASE_COUNT - passed)) /
                 (double)TEST_CASE_COUNT);

    (void)printf("========================================\n");

    return (passed == TEST_CASE_COUNT) ? EXIT_SUCCESS : EXIT_FAILURE;
}
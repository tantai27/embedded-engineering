#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "string_reverse.h"

#define TEST_CASE_COUNT    (8U)
#define TEST_BUFFER_SIZE   (32U)

typedef struct
{
    const char *name;
    const char *input;
    const char *expected;
} test_case_t;

static uint32_t run_test(const test_case_t * const test_case,
                         const uint32_t test_number)
{
    char buffer[TEST_BUFFER_SIZE];
    string_reverse_status_t status;

    (void)strncpy(buffer,
                  test_case->input,
                  TEST_BUFFER_SIZE - 1U);

    buffer[TEST_BUFFER_SIZE - 1U] = '\0';

    status = string_reverse(buffer);

    if ((STRING_REVERSE_STATUS_SUCCESS == status) &&
        (0 == strcmp(buffer, test_case->expected)))
    {
        (void)printf("[%02u/%02u] %-30s [PASS]\n",
                     test_number,
                     TEST_CASE_COUNT,
                     test_case->name);

        return 1U;
    }

    (void)printf("[%02u/%02u] %-30s [FAIL]\n",
                 test_number,
                 TEST_CASE_COUNT,
                 test_case->name);

    (void)printf("         Expected: \"%s\"\n",
                 test_case->expected);

    (void)printf("         Actual  : \"%s\"\n",
                 buffer);

    return 0U;
}

int main(void)
{
    static const test_case_t test_cases[] =
    {
        {
            "Reverse normal string",
            "Embedded",
            "deddebmE"
        },
        {
            "Reverse single character",
            "A",
            "A"
        },
        {
            "Reverse two characters",
            "AB",
            "BA"
        },
        {
            "Reverse even length",
            "ABCD",
            "DCBA"
        },
        {
            "Reverse odd length",
            "ABCDE",
            "EDCBA"
        },
        {
            "Reverse string with spaces",
            "Hello World",
            "dlroW olleH"
        },
        {
            "Reverse empty string",
            "",
            ""
        },
        {
            "Reverse string with numbers",
            "ABC123",
            "321CBA"
        }
    };

    uint32_t passed = 0U;
    uint32_t index = 0U;

    (void)printf("========================================\n");
    (void)printf("Running string_reverse unit tests\n");
    (void)printf("========================================\n");

    for (index = 0U; index < TEST_CASE_COUNT; ++index)
    {
        passed += run_test(&test_cases[index],
                           index + 1U);
    }

    {
        string_reverse_status_t status;

        status = string_reverse(NULL);

        if (STRING_REVERSE_STATUS_INVALID_ARGUMENT == status)
        {
            (void)printf("[%02u/%02u] %-30s [PASS]\n",
                         TEST_CASE_COUNT,
                         TEST_CASE_COUNT,
                         "Null pointer");

            ++passed;
        }
        else
        {
            (void)printf("[%02u/%02u] %-30s [FAIL]\n",
                         TEST_CASE_COUNT,
                         TEST_CASE_COUNT,
                         "Null pointer");
        }
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
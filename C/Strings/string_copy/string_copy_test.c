#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "string_copy.h"

#define TEST_CASE_COUNT (9U)

typedef struct
{
    const char *name;
    char *dest;
    uint32_t dest_size;
    const char *src;
    string_copy_status_t expected_status;
    const char *expected_dest;
} test_case_t;

static uint32_t run_test(const test_case_t * const test_case,
                         const uint32_t test_number)
{
    const string_copy_status_t actual_status =
        string_copy(test_case->dest,
                    test_case->dest_size,
                    test_case->src);

    if ((actual_status == test_case->expected_status) &&
        ((STRING_COPY_STATUS_SUCCESS != actual_status) ||
         (0 == strcmp(test_case->dest, test_case->expected_dest))))
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

    (void)printf("         Expected status: %u, Actual status: %u\n",
                 (uint32_t)test_case->expected_status,
                 (uint32_t)actual_status);

    if (STRING_COPY_STATUS_SUCCESS == test_case->expected_status)
    {
        (void)printf("         Expected string: \"%s\"\n",
                     test_case->expected_dest);
        (void)printf("         Actual string  : \"%s\"\n",
                     test_case->dest);
    }

    return 0U;
}

int main(void)
{
    static const test_case_t test_cases[] =
    {
        {
            "Normal string copy",
            (char[16U]){0},
            16U,
            "hello",
            STRING_COPY_STATUS_SUCCESS,
            "hello"
        },
        {
            "Empty string",
            (char[8U]){0},
            8U,
            "",
            STRING_COPY_STATUS_SUCCESS,
            ""
        },
        {
            "Exact buffer size",
            (char[6U]){0},
            6U,
            "hello",
            STRING_COPY_STATUS_SUCCESS,
            "hello"
        },
        {
            "Buffer too small",
            (char[5U]){0},
            5U,
            "hello",
            STRING_COPY_STATUS_BUFFER_TOO_SMALL,
            NULL
        },
        {
            "One byte buffer",
            (char[1U]){0},
            1U,
            "",
            STRING_COPY_STATUS_SUCCESS,
            ""
        },
        {
            "One byte buffer too small",
            (char[1U]){0},
            1U,
            "A",
            STRING_COPY_STATUS_BUFFER_TOO_SMALL,
            NULL
        },
        {
            "Null destination",
            NULL,
            8U,
            "hello",
            STRING_COPY_STATUS_INVALID_ARGUMENT,
            NULL
        },
        {
            "Null source",
            (char[8U]){0},
            8U,
            NULL,
            STRING_COPY_STATUS_INVALID_ARGUMENT,
            NULL
        },
        {
            "Zero destination size",
            (char[8U]){0},
            0U,
            "hello",
            STRING_COPY_STATUS_INVALID_ARGUMENT,
            NULL
        }
    };

    uint32_t index = 0U;
    uint32_t passed = 0U;

    (void)printf("========================================\n");
    (void)printf("Running string_copy unit tests\n");
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
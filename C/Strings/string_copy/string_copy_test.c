#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "string_copy.h"

#define TEST_PASS         (0)
#define TEST_FAIL         (1)

#define TEST_CASE_COUNT   (9U)

typedef struct
{
    const char *name;
    int (*function)(void);
} test_case_t;

static uint32_t total_tests = 0U;
static uint32_t passed_tests = 0U;

static void report_test(const uint32_t test_number,
                        const uint32_t planned_tests,
                        const char *name,
                        const int result)
{
    ++total_tests;

    if (TEST_PASS == result)
    {
        ++passed_tests;
    }

    (void)printf("[%02u/%02u] %-30s [%s]\n",
                 test_number,
                 planned_tests,
                 name,
                 (TEST_PASS == result) ? "PASS" : "FAIL");
}

static int test_normal_string_copy(void)
{
    char dest[16U] = {0};

    if (STRING_COPY_STATUS_SUCCESS !=
        string_copy(dest, sizeof(dest), "hello"))
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(dest, "hello"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_empty_string(void)
{
    char dest[8U] = {0};

    if (STRING_COPY_STATUS_SUCCESS !=
        string_copy(dest, sizeof(dest), ""))
    {
        return TEST_FAIL;
    }

    if ('\0' != dest[0])
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_exact_buffer_size(void)
{
    char dest[6U] = {0};

    if (STRING_COPY_STATUS_SUCCESS !=
        string_copy(dest, sizeof(dest), "hello"))
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(dest, "hello"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_buffer_too_small(void)
{
    char dest[5U] = {0};

    if (STRING_COPY_STATUS_BUFFER_TOO_SMALL !=
        string_copy(dest, sizeof(dest), "hello"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_one_byte_buffer(void)
{
    char dest[1U] = {0};

    if (STRING_COPY_STATUS_SUCCESS !=
        string_copy(dest, sizeof(dest), ""))
    {
        return TEST_FAIL;
    }

    if ('\0' != dest[0])
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_one_byte_buffer_too_small(void)
{
    char dest[1U] = {0};

    if (STRING_COPY_STATUS_BUFFER_TOO_SMALL !=
        string_copy(dest, sizeof(dest), "A"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_destination(void)
{
    if (STRING_COPY_STATUS_INVALID_ARGUMENT !=
        string_copy(NULL, 8U, "hello"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_source(void)
{
    char dest[8U] = {0};

    if (STRING_COPY_STATUS_INVALID_ARGUMENT !=
        string_copy(dest, sizeof(dest), NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_zero_destination_size(void)
{
    char dest[8U] = {0};

    if (STRING_COPY_STATUS_INVALID_ARGUMENT !=
        string_copy(dest, 0U, "hello"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int main(void)
{
    static const test_case_t test_cases[TEST_CASE_COUNT] =
    {
        {
            "Normal string copy",
            test_normal_string_copy
        },
        {
            "Empty string",
            test_empty_string
        },
        {
            "Exact buffer size",
            test_exact_buffer_size
        },
        {
            "Buffer too small",
            test_buffer_too_small
        },
        {
            "One byte buffer",
            test_one_byte_buffer
        },
        {
            "One byte buffer too small",
            test_one_byte_buffer_too_small
        },
        {
            "Null destination",
            test_null_destination
        },
        {
            "Null source",
            test_null_source
        },
        {
            "Zero destination size",
            test_zero_destination_size
        }
    };

    uint32_t index = 0U;
    int result = TEST_PASS;

    (void)printf("========================================\n");
    (void)printf("Running string_copy unit tests\n");
    (void)printf("========================================\n");

    for (index = 0U; index < TEST_CASE_COUNT; ++index)
    {
        result = test_cases[index].function();

        report_test(index + 1U,
                    TEST_CASE_COUNT,
                    test_cases[index].name,
                    result);
    }

    (void)printf("----------------------------------------\n");
    (void)printf("Summary\n");
    (void)printf("----------------------------------------\n");

    (void)printf("Executed : %u/%u\n",
                 total_tests,
                 TEST_CASE_COUNT);

    (void)printf("Passed   : %u/%u (%.0f%%)\n",
                 passed_tests,
                 TEST_CASE_COUNT,
                 (100.0 * (double)passed_tests) /
                 (double)TEST_CASE_COUNT);

    (void)printf("Failed   : %u/%u (%.0f%%)\n",
                 total_tests - passed_tests,
                 TEST_CASE_COUNT,
                 (100.0 * (double)(total_tests - passed_tests)) /
                 (double)TEST_CASE_COUNT);

    (void)printf("========================================\n");

    return (passed_tests == TEST_CASE_COUNT)
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}
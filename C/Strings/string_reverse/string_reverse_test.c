#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "string_reverse.h"

#define TEST_PASS          (0)
#define TEST_FAIL          (1)

#define TEST_CASE_COUNT    (9U)
#define TEST_BUFFER_SIZE   (32U)

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

static int test_reverse_normal_string(void)
{
    char buffer[TEST_BUFFER_SIZE] = {0};
    string_reverse_status_t status;

    (void)strncpy(buffer,
                  "Embedded",
                  TEST_BUFFER_SIZE - 1U);

    buffer[TEST_BUFFER_SIZE - 1U] = '\0';

    status = string_reverse(buffer);

    if (STRING_REVERSE_STATUS_SUCCESS != status)
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(buffer, "deddebmE"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_reverse_single_character(void)
{
    char buffer[TEST_BUFFER_SIZE] = {0};
    string_reverse_status_t status;

    (void)strncpy(buffer,
                  "A",
                  TEST_BUFFER_SIZE - 1U);

    buffer[TEST_BUFFER_SIZE - 1U] = '\0';

    status = string_reverse(buffer);

    if (STRING_REVERSE_STATUS_SUCCESS != status)
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(buffer, "A"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_reverse_two_characters(void)
{
    char buffer[TEST_BUFFER_SIZE] = {0};
    string_reverse_status_t status;

    (void)strncpy(buffer,
                  "AB",
                  TEST_BUFFER_SIZE - 1U);

    buffer[TEST_BUFFER_SIZE - 1U] = '\0';

    status = string_reverse(buffer);

    if (STRING_REVERSE_STATUS_SUCCESS != status)
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(buffer, "BA"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_reverse_even_length(void)
{
    char buffer[TEST_BUFFER_SIZE] = {0};
    string_reverse_status_t status;

    (void)strncpy(buffer,
                  "ABCD",
                  TEST_BUFFER_SIZE - 1U);

    buffer[TEST_BUFFER_SIZE - 1U] = '\0';

    status = string_reverse(buffer);

    if (STRING_REVERSE_STATUS_SUCCESS != status)
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(buffer, "DCBA"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_reverse_odd_length(void)
{
    char buffer[TEST_BUFFER_SIZE] = {0};
    string_reverse_status_t status;

    (void)strncpy(buffer,
                  "ABCDE",
                  TEST_BUFFER_SIZE - 1U);

    buffer[TEST_BUFFER_SIZE - 1U] = '\0';

    status = string_reverse(buffer);

    if (STRING_REVERSE_STATUS_SUCCESS != status)
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(buffer, "EDCBA"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_reverse_string_with_spaces(void)
{
    char buffer[TEST_BUFFER_SIZE] = {0};
    string_reverse_status_t status;

    (void)strncpy(buffer,
                  "Hello World",
                  TEST_BUFFER_SIZE - 1U);

    buffer[TEST_BUFFER_SIZE - 1U] = '\0';

    status = string_reverse(buffer);

    if (STRING_REVERSE_STATUS_SUCCESS != status)
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(buffer, "dlroW olleH"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_reverse_empty_string(void)
{
    char buffer[TEST_BUFFER_SIZE] = {0};
    string_reverse_status_t status;

    status = string_reverse(buffer);

    if (STRING_REVERSE_STATUS_SUCCESS != status)
    {
        return TEST_FAIL;
    }

    if ('\0' != buffer[0])
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_reverse_string_with_numbers(void)
{
    char buffer[TEST_BUFFER_SIZE] = {0};
    string_reverse_status_t status;

    (void)strncpy(buffer,
                  "ABC123",
                  TEST_BUFFER_SIZE - 1U);

    buffer[TEST_BUFFER_SIZE - 1U] = '\0';

    status = string_reverse(buffer);

    if (STRING_REVERSE_STATUS_SUCCESS != status)
    {
        return TEST_FAIL;
    }

    if (0 != strcmp(buffer, "321CBA"))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_pointer(void)
{
    if (STRING_REVERSE_STATUS_INVALID_ARGUMENT !=
        string_reverse(NULL))
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
            "Reverse normal string",
            test_reverse_normal_string
        },
        {
            "Reverse single character",
            test_reverse_single_character
        },
        {
            "Reverse two characters",
            test_reverse_two_characters
        },
        {
            "Reverse even length",
            test_reverse_even_length
        },
        {
            "Reverse odd length",
            test_reverse_odd_length
        },
        {
            "Reverse string with spaces",
            test_reverse_string_with_spaces
        },
        {
            "Reverse empty string",
            test_reverse_empty_string
        },
        {
            "Reverse string with numbers",
            test_reverse_string_with_numbers
        },
        {
            "Null pointer",
            test_null_pointer
        }
    };

    uint32_t index = 0U;
    int result = TEST_PASS;

    (void)printf("========================================\n");
    (void)printf("Running string_reverse unit tests\n");
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
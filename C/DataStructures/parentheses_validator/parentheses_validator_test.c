#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "parentheses_validator.h"

#define TEST_CASE_COUNT       (12U)
#define TEST_STACK_CAPACITY   (32U)

typedef struct
{
    const char *name;
    const char *input;
    parentheses_status_t expected_status;
} test_case_t;

static uint32_t run_test(const test_case_t * const test_case,
                         const uint32_t test_number)
{
    const parentheses_status_t actual_status =
        parentheses_validate(test_case->input);

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
            "Empty string",
            "",
            PARENTHESES_STATUS_VALID
        },
        {
            "No brackets",
            "Embedded C",
            PARENTHESES_STATUS_VALID
        },
        {
            "Simple pair",
            "()",
            PARENTHESES_STATUS_VALID
        },
        {
            "Multiple pairs",
            "()[]{}",
            PARENTHESES_STATUS_VALID
        },
        {
            "Nested brackets",
            "{[()]}",
            PARENTHESES_STATUS_VALID
        },
        {
            "Mismatched brackets",
            "{[(])}",
            PARENTHESES_STATUS_INVALID
        },
        {
            "Incorrect ordering",
            "([)]",
            PARENTHESES_STATUS_INVALID
        },
        {
            "Unclosed brackets",
            "(((",
            PARENTHESES_STATUS_INVALID
        },
        {
            "Unexpected closing bracket",
            "}",
            PARENTHESES_STATUS_INVALID
        },
        {
            "Null input",
            NULL,
            PARENTHESES_STATUS_INVALID_ARGUMENT
        }
    };

    char max_depth_input[(TEST_STACK_CAPACITY * 2U) + 1U];
    char overflow_input[TEST_STACK_CAPACITY + 2U];

    test_case_t max_depth_test;
    test_case_t overflow_test;

    uint32_t index = 0U;
    uint32_t passed = 0U;

    for (index = 0U; index < TEST_STACK_CAPACITY; ++index)
    {
        max_depth_input[index] = '(';
        max_depth_input[TEST_STACK_CAPACITY + index] = ')';
    }

    max_depth_input[TEST_STACK_CAPACITY * 2U] = '\0';

    for (index = 0U; index < TEST_STACK_CAPACITY + 1U; ++index)
    {
        overflow_input[index] = '(';
    }

    overflow_input[TEST_STACK_CAPACITY + 1U] = '\0';

    max_depth_test.name = "Maximum nesting depth";
    max_depth_test.input = max_depth_input;
    max_depth_test.expected_status = PARENTHESES_STATUS_VALID;

    overflow_test.name = "Stack overflow";
    overflow_test.input = overflow_input;
    overflow_test.expected_status = PARENTHESES_STATUS_OVERFLOW;

    (void)printf("========================================\n");
    (void)printf("Running parentheses_validator unit tests\n");
    (void)printf("========================================\n");

    for (index = 0U; index < 10U; ++index)
    {
        passed += run_test(&test_cases[index], index + 1U);
    }

    passed += run_test(&max_depth_test, 11U);
    passed += run_test(&overflow_test, 12U);

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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "clear_bit.h"

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

static int test_clear_bit_0(void)
{
    uint32_t reg = 0xFFFFFFFFUL;

    if (STATUS_SUCCESS != clear_bit(&reg, 0U))
    {
        return TEST_FAIL;
    }

    if (0xFFFFFFFEUL != reg)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_clear_bit_31(void)
{
    uint32_t reg = 0xFFFFFFFFUL;

    if (STATUS_SUCCESS != clear_bit(&reg, 31U))
    {
        return TEST_FAIL;
    }

    if (0x7FFFFFFFUL != reg)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_clear_bit_already_clear(void)
{
    uint32_t reg = 0U;

    if (STATUS_SUCCESS != clear_bit(&reg, 31U))
    {
        return TEST_FAIL;
    }

    if (0x00000000UL != reg)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_clear_bit_non_zero_register(void)
{
    uint32_t reg = 0xAAAAAAABUL;

    if (STATUS_SUCCESS != clear_bit(&reg, 0U))
    {
        return TEST_FAIL;
    }

    if (0xAAAAAAAAUL != reg)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_pointer(void)
{
    if (STATUS_INVALID_ARGUMENT != clear_bit(NULL, 5U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_invalid_bit(void)
{
    uint32_t reg = 0U;

    if (STATUS_INVALID_ARGUMENT != clear_bit(&reg, 32U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static const test_case_t test_cases[] =
{
    { "Clear bit 0",                    test_clear_bit_0 },
    { "Clear bit 31",                   test_clear_bit_31 },
    { "Clear already-clear bit",        test_clear_bit_already_clear },
    { "Clear bit on non-zero register", test_clear_bit_non_zero_register },
    { "Null pointer",                   test_null_pointer },
    { "Invalid bit position",           test_invalid_bit }
};

int main(void)
{
    const uint32_t planned_tests =
        (uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));

    (void)printf("========================================\n");
    (void)printf("Running clear_bit unit tests\n");
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

    return (failed_tests == 0U) ? EXIT_SUCCESS : EXIT_FAILURE;
}
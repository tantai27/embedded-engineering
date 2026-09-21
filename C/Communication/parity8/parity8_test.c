#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "parity8.h"

#define TEST_PASS        (0)
#define TEST_FAIL        (1)

#define TEST_CASE_COUNT  (10U)

typedef struct
{
    const char *description;
    int (*function)(void);
} test_case_t;

static uint32_t total_tests = 0U;
static uint32_t passed_tests = 0U;

static void report_test(uint32_t test_number,
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
                 test_number,
                 planned_tests,
                 description,
                 (TEST_PASS == result) ? "PASS" : "FAIL");
}

static int test_even_parity_zero(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_SUCCESS !=
        parity8_calculate(0x00U, PARITY8_EVEN, &parity))
    {
        return TEST_FAIL;
    }

    if (0U != parity)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_even_parity_all_ones(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_SUCCESS !=
        parity8_calculate(0xFFU, PARITY8_EVEN, &parity))
    {
        return TEST_FAIL;
    }

    if (0U != parity)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_even_parity_odd_number_of_bits(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_SUCCESS !=
        parity8_calculate(0x01U, PARITY8_EVEN, &parity))
    {
        return TEST_FAIL;
    }

    if (1U != parity)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_even_parity_even_number_of_bits(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_SUCCESS !=
        parity8_calculate(0x03U, PARITY8_EVEN, &parity))
    {
        return TEST_FAIL;
    }

    if (0U != parity)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_odd_parity_odd_number_of_bits(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_SUCCESS !=
        parity8_calculate(0x01U, PARITY8_ODD, &parity))
    {
        return TEST_FAIL;
    }

    if (0U != parity)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_odd_parity_even_number_of_bits(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_SUCCESS !=
        parity8_calculate(0x03U, PARITY8_ODD, &parity))
    {
        return TEST_FAIL;
    }

    if (1U != parity)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_even_parity_alternating_bits(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_SUCCESS !=
        parity8_calculate(0xAAU, PARITY8_EVEN, &parity))
    {
        return TEST_FAIL;
    }

    if (0U != parity)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_odd_parity_alternating_bits(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_SUCCESS !=
        parity8_calculate(0x55U, PARITY8_ODD, &parity))
    {
        return TEST_FAIL;
    }

    if (1U != parity)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_output_pointer(void)
{
    if (PARITY8_STATUS_INVALID_ARGUMENT !=
        parity8_calculate(0x55U, PARITY8_EVEN, NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_invalid_parity_type(void)
{
    uint8_t parity = 0U;

    if (PARITY8_STATUS_INVALID_ARGUMENT !=
        parity8_calculate(0x55U,
                          (parity8_type_t)2U,
                          &parity))
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
            "Even parity zero",
            test_even_parity_zero
        },
        {
            "Even parity all ones",
            test_even_parity_all_ones
        },
        {
            "Even parity odd set bits",
            test_even_parity_odd_number_of_bits
        },
        {
            "Even parity even set bits",
            test_even_parity_even_number_of_bits
        },
        {
            "Odd parity odd set bits",
            test_odd_parity_odd_number_of_bits
        },
        {
            "Odd parity even set bits",
            test_odd_parity_even_number_of_bits
        },
        {
            "Even parity alternating bits",
            test_even_parity_alternating_bits
        },
        {
            "Odd parity alternating bits",
            test_odd_parity_alternating_bits
        },
        {
            "Null output pointer",
            test_null_output_pointer
        },
        {
            "Invalid parity type",
            test_invalid_parity_type
        }
    };

    uint32_t index = 0U;
    int result = TEST_PASS;

    (void)printf("========================================\n");
    (void)printf("Running parity8 unit tests\n");
    (void)printf("========================================\n");

    for (index = 0U; index < TEST_CASE_COUNT; ++index)
    {
        result = test_cases[index].function();

        report_test(index + 1U,
                    TEST_CASE_COUNT,
                    test_cases[index].description,
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
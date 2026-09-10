#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "bit_extract.h"

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

static int test_extract_bit_zero(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0x00000001UL, 0U, 1U, &result))
    {
        return TEST_FAIL;
    }

    if (0x00000001UL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_bit_seven(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0x00000080UL, 7U, 1U, &result))
    {
        return TEST_FAIL;
    }

    if (0x00000001UL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_bit_thirty_one(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0x80000000UL, 31U, 1U, &result))
    {
        return TEST_FAIL;
    }

    if (0x00000001UL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_multiple_bits(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0x000000B4UL, 2U, 4U, &result))
    {
        return TEST_FAIL;
    }

    if (0x0000000DUL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_non_byte_aligned_field(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0x000000B4UL, 3U, 5U, &result))
    {
        return TEST_FAIL;
    }

    if (0x00000016UL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_middle_byte(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0xABCD1234UL, 8U, 8U, &result))
    {
        return TEST_FAIL;
    }

    if (0x00000012UL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_upper_byte(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0xABCD1234UL, 24U, 8U, &result))
    {
        return TEST_FAIL;
    }

    if (0x000000ABUL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_width_sixteen(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0x12345678UL, 0U, 16U, &result))
    {
        return TEST_FAIL;
    }

    if (0x00005678UL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_width_thirty_one(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0xFFFFFFFFUL, 1U, 31U, &result))
    {
        return TEST_FAIL;
    }

    if (0x7FFFFFFFUL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_full_width(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0xA5A5A5A5UL, 0U, 32U, &result))
    {
        return TEST_FAIL;
    }

    if (0xA5A5A5A5UL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_all_zero(void)
{
    uint32_t result = 0xFFFFFFFFUL;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0x00000000UL, 4U, 8U, &result))
    {
        return TEST_FAIL;
    }

    if (0x00000000UL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_all_one(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0xFFFFFFFFUL, 4U, 8U, &result))
    {
        return TEST_FAIL;
    }

    if (0x000000FFUL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_lower_boundary(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0x000000FFUL, 0U, 8U, &result))
    {
        return TEST_FAIL;
    }

    if (0x000000FFUL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_upper_boundary(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0xFF000000UL, 24U, 8U, &result))
    {
        return TEST_FAIL;
    }

    if (0x000000FFUL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_field_ends_at_bit_thirty_one(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_SUCCESS !=
        bit_extract(0xFFFF0000UL, 16U, 16U, &result))
    {
        return TEST_FAIL;
    }

    if (0x0000FFFFUL != result)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_null_result(void)
{
    if (BIT_EXTRACT_STATUS_INVALID_ARGUMENT !=
        bit_extract(0x12345678UL, 0U, 8U, NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_zero_width(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_INVALID_ARGUMENT !=
        bit_extract(0x12345678UL, 0U, 0U, &result))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_invalid_position(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_INVALID_ARGUMENT !=
        bit_extract(0x12345678UL, 32U, 1U, &result))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_field_exceeds_width(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_INVALID_ARGUMENT !=
        bit_extract(0x12345678UL, 28U, 5U, &result))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_msb_field_exceeds_width(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_INVALID_ARGUMENT !=
        bit_extract(0xFFFFFFFFUL, 31U, 2U, &result))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_extract_position_and_width_exceed_limit(void)
{
    uint32_t result = 0U;

    if (BIT_EXTRACT_STATUS_INVALID_ARGUMENT !=
        bit_extract(0xFFFFFFFFUL, 16U, 17U, &result))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static const test_case_t test_cases[] =
{
    { "Extract bit 0",                    test_extract_bit_zero },
    { "Extract bit 7",                    test_extract_bit_seven },
    { "Extract bit 31",                   test_extract_bit_thirty_one },
    { "Extract multiple bits",            test_extract_multiple_bits },
    { "Extract non-byte-aligned field",   test_extract_non_byte_aligned_field },
    { "Extract middle byte",              test_extract_middle_byte },
    { "Extract upper byte",               test_extract_upper_byte },
    { "Extract 16-bit field",             test_extract_width_sixteen },
    { "Extract 31-bit field",             test_extract_width_thirty_one },
    { "Extract full 32-bit field",        test_extract_full_width },
    { "Extract from all-zero value",      test_extract_all_zero },
    { "Extract from all-one value",       test_extract_all_one },
    { "Extract lower boundary",           test_extract_lower_boundary },
    { "Extract upper boundary",           test_extract_upper_boundary },
    { "Field ends at bit 31",             test_extract_field_ends_at_bit_thirty_one },
    { "Null result pointer",              test_extract_null_result },
    { "Zero field width",                 test_extract_zero_width },
    { "Invalid bit position",             test_extract_invalid_position },
    { "Field exceeds value width",        test_extract_field_exceeds_width },
    { "MSB field exceeds width",          test_extract_msb_field_exceeds_width },
    { "Position and width exceed limit",  test_extract_position_and_width_exceed_limit }
};

int main(void)
{
    const uint32_t planned_tests =
        (uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));

    (void)printf("========================================\n");
    (void)printf("Running bit_extract unit tests\n");
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
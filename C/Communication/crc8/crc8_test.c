#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "crc8.h"

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

static int test_crc8_known_vector(void)
{
    static const uint8_t data[] = "123456789";
    uint8_t crc = 0U;

    if (CRC8_STATUS_SUCCESS !=
        crc8_calculate(data,
                       (uint32_t)(sizeof(data) - 1U),
                       &crc))
    {
        return TEST_FAIL;
    }

    if (0xF4U != crc)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_crc8_single_zero_byte(void)
{
    const uint8_t data[] = { 0x00U };
    uint8_t crc = 0U;

    if (CRC8_STATUS_SUCCESS !=
        crc8_calculate(data, 1U, &crc))
    {
        return TEST_FAIL;
    }

    if (0x00U != crc)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_crc8_single_byte(void)
{
    const uint8_t data[] = { 0x01U };
    uint8_t crc = 0U;

    if (CRC8_STATUS_SUCCESS !=
        crc8_calculate(data, 1U, &crc))
    {
        return TEST_FAIL;
    }

    if (0x07U != crc)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_crc8_multiple_bytes(void)
{
    const uint8_t data[] =
    {
        0x01U, 0x02U, 0x03U, 0x04U, 0x05U
    };
    uint8_t crc = 0U;

    if (CRC8_STATUS_SUCCESS !=
        crc8_calculate(data, 5U, &crc))
    {
        return TEST_FAIL;
    }

    if (0xBCU != crc)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_crc8_empty_input(void)
{
    const uint8_t data[] = { 0xAAU };
    uint8_t crc = 0xFFU;

    if (CRC8_STATUS_SUCCESS !=
        crc8_calculate(data, 0U, &crc))
    {
        return TEST_FAIL;
    }

    if (0x00U != crc)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_crc8_null_data(void)
{
    uint8_t crc = 0U;

    if (CRC8_STATUS_INVALID_ARGUMENT !=
        crc8_calculate(NULL, 1U, &crc))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_crc8_null_output(void)
{
    const uint8_t data[] = { 0x01U };

    if (CRC8_STATUS_INVALID_ARGUMENT !=
        crc8_calculate(data, 1U, NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static const test_case_t test_cases[] =
{
    { "Known CRC vector",       test_crc8_known_vector },
    { "Single zero byte",       test_crc8_single_zero_byte },
    { "Single byte",            test_crc8_single_byte },
    { "Multiple bytes",         test_crc8_multiple_bytes },
    { "Empty input",            test_crc8_empty_input },
    { "Null data pointer",      test_crc8_null_data },
    { "Null output pointer",    test_crc8_null_output }
};

int main(void)
{
    const uint32_t planned_tests =
        (uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));

    (void)printf("========================================\n");
    (void)printf("Running crc8 unit tests\n");
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

    return (0U == failed_tests) ? EXIT_SUCCESS : EXIT_FAILURE;
}
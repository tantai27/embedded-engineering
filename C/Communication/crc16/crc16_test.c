#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "crc16.h"

#define TEST_PASS    (0)
#define TEST_FAIL    (1)

typedef struct
{
    const char *description;
    const uint8_t *data;
    uint32_t length;
    uint16_t expected_crc;
    crc16_status_t expected_status;
    uint8_t null_output;
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

static int run_test(const test_case_t * const test_case)
{
    uint16_t actual_crc = 0U;
    uint16_t *output_crc = &actual_crc;

    if (0U != test_case->null_output)
    {
        output_crc = NULL;
    }

    const crc16_status_t actual_status =
        crc16_calculate(test_case->data,
                        test_case->length,
                        output_crc);

    if (actual_status != test_case->expected_status)
    {
        (void)printf("         Expected status: %u, Actual status: %u\n",
                     (uint32_t)test_case->expected_status,
                     (uint32_t)actual_status);

        return TEST_FAIL;
    }

    if (CRC16_STATUS_SUCCESS == test_case->expected_status)
    {
        if (actual_crc != test_case->expected_crc)
        {
            (void)printf("         Expected CRC   : 0x%04X\n",
                         test_case->expected_crc);

            (void)printf("         Actual CRC     : 0x%04X\n",
                         actual_crc);

            return TEST_FAIL;
        }
    }

    return TEST_PASS;
}

int main(void)
{
    static const uint8_t data_empty[] =
    {
        0x00U
    };

    static const uint8_t data_123456789[] =
    {
        0x31U, 0x32U, 0x33U, 0x34U, 0x35U,
        0x36U, 0x37U, 0x38U, 0x39U
    };

    static const uint8_t data_single[] =
    {
        0x00U
    };

    static const uint8_t data_binary[] =
    {
        0x10U, 0x20U, 0x30U, 0x40U
    };

    static const test_case_t test_cases[] =
    {
        {
            "CRC-16/IBM known vector",
            data_123456789,
            9U,
            0xBB3DU,
            CRC16_STATUS_SUCCESS,
            0U
        },
        {
            "Single zero byte",
            data_single,
            1U,
            0x0000U,
            CRC16_STATUS_SUCCESS,
            0U
        },
        {
            "Binary data",
            data_binary,
            4U,
            0xFA10U,
            CRC16_STATUS_SUCCESS,
            0U
        },
        {
            "Zero length",
            data_empty,
            0U,
            0x0000U,
            CRC16_STATUS_SUCCESS,
            0U
        },
        {
            "Null data pointer",
            NULL,
            4U,
            0x0000U,
            CRC16_STATUS_INVALID_ARGUMENT,
            0U
        },
        {
            "Null output pointer",
            data_binary,
            4U,
            0x0000U,
            CRC16_STATUS_INVALID_ARGUMENT,
            1U
        },
        {
            "Null data and output",
            NULL,
            4U,
            0x0000U,
            CRC16_STATUS_INVALID_ARGUMENT,
            1U
        },
        {
            "Empty data with valid output",
            data_empty,
            0U,
            0x0000U,
            CRC16_STATUS_SUCCESS,
            0U
        }
    };

    const uint32_t planned_tests =
        (uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));

    (void)printf("========================================\n");
    (void)printf("Running crc16 unit tests\n");
    (void)printf("========================================\n");

    for (uint32_t i = 0U; i < planned_tests; ++i)
    {
        const int result = run_test(&test_cases[i]);

        report_test(i + 1U,
                    planned_tests,
                    test_cases[i].description,
                    result);
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
                 (100.0 * (double)passed_tests) /
                 (double)planned_tests);

    (void)printf("Failed   : %u/%u (%.0f%%)\n",
                 failed_tests,
                 planned_tests,
                 (100.0 * (double)failed_tests) /
                 (double)planned_tests);

    (void)printf("========================================\n");

    return (failed_tests == 0U) ? EXIT_SUCCESS : EXIT_FAILURE;
}
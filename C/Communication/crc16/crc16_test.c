#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "crc16.h"

#define TEST_CASE_COUNT (8U)

typedef struct
{
    const char *name;
    const uint8_t *data;
    uint32_t length;
    uint16_t expected_crc;
    crc16_status_t expected_status;
} test_case_t;

static uint32_t run_test(const test_case_t * const test_case,
                         const uint32_t test_number)
{
    uint16_t actual_crc = 0U;

    const crc16_status_t actual_status =
        crc16_calculate(test_case->data,
                        test_case->length,
                        &actual_crc);

    if ((actual_status == test_case->expected_status) &&
        ((CRC16_STATUS_SUCCESS != actual_status) ||
         (actual_crc == test_case->expected_crc)))
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

    if (CRC16_STATUS_SUCCESS == test_case->expected_status)
    {
        (void)printf("         Expected CRC   : 0x%04X\n",
                     test_case->expected_crc);

        (void)printf("         Actual CRC     : 0x%04X\n",
                     actual_crc);
    }

    return 0U;
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
            CRC16_STATUS_SUCCESS
        },
        {
            "Single zero byte",
            data_single,
            1U,
            0x0000U,
            CRC16_STATUS_SUCCESS
        },
        {
            "Binary data",
            data_binary,
            4U,
            0x3C0AU,
            CRC16_STATUS_SUCCESS
        },
        {
            "Zero length",
            data_empty,
            0U,
            0x0000U,
            CRC16_STATUS_SUCCESS
        },
        {
            "Null data pointer",
            NULL,
            4U,
            0x0000U,
            CRC16_STATUS_INVALID_ARGUMENT
        },
        {
            "Null output pointer",
            data_binary,
            4U,
            0x0000U,
            CRC16_STATUS_INVALID_ARGUMENT
        },
        {
            "Null data and output",
            NULL,
            4U,
            0x0000U,
            CRC16_STATUS_INVALID_ARGUMENT
        },
        {
            "Empty data with valid output",
            data_empty,
            0U,
            0x0000U,
            CRC16_STATUS_SUCCESS
        }
    };

    uint32_t index = 0U;
    uint32_t passed = 0U;

    (void)printf("========================================\n");
    (void)printf("Running crc16 unit tests\n");
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
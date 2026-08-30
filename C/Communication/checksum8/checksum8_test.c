#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "checksum8.h"

#define TEST_CASE_COUNT    (8U)

static uint32_t run_test(const char * const test_name,
                         uint32_t test_number,
                         uint32_t expected,
                         uint32_t actual)
{
    if (expected == actual)
    {
        (void)printf("[%02u/%02u] %-30s [PASS]\n",
                     test_number,
                     TEST_CASE_COUNT,
                     test_name);

        return 1U;
    }

    (void)printf("[%02u/%02u] %-30s [FAIL]\n",
                 test_number,
                 TEST_CASE_COUNT,
                 test_name);

    (void)printf("         Expected: %u, Actual: %u\n",
                 expected,
                 actual);

    return 0U;
}

int main(void)
{
    const uint8_t test_data[] =
    {
        0x01U, 0x02U, 0x03U, 0x04U
    };

    const uint8_t overflow_data[] =
    {
        0xFFU, 0x01U
    };

    const uint8_t single_byte_data[] =
    {
        0xA5U
    };

    uint8_t checksum = 0U;
    uint32_t passed = 0U;
    uint32_t test_number = 1U;
    checksum8_status_t status;

    (void)printf("========================================\n");
    (void)printf("Running checksum8 unit tests\n");
    (void)printf("========================================\n");

    status = checksum8_calculate(test_data,
                                 sizeof(test_data),
                                 &checksum);

    passed += run_test("Basic checksum",
                       test_number++,
                       CHECKSUM8_STATUS_SUCCESS,
                       status);

    passed += run_test("Basic checksum value",
                       test_number++,
                       0x0AU,
                       checksum);

    status = checksum8_calculate(overflow_data,
                                 sizeof(overflow_data),
                                 &checksum);

    passed += run_test("Checksum overflow",
                       test_number++,
                       CHECKSUM8_STATUS_SUCCESS,
                       status);

    passed += run_test("Overflow checksum value",
                       test_number++,
                       0x00U,
                       checksum);

    status = checksum8_calculate(single_byte_data,
                                 sizeof(single_byte_data),
                                 &checksum);

    passed += run_test("Single byte checksum",
                       test_number++,
                       0xA5U,
                       checksum);

    status = checksum8_calculate(NULL,
                                 sizeof(test_data),
                                 &checksum);

    passed += run_test("Null data pointer",
                       test_number++,
                       CHECKSUM8_STATUS_INVALID_ARGUMENT,
                       status);

    status = checksum8_calculate(test_data,
                                 sizeof(test_data),
                                 NULL);

    passed += run_test("Null output pointer",
                       test_number++,
                       CHECKSUM8_STATUS_INVALID_ARGUMENT,
                       status);

    status = checksum8_calculate(NULL,
                                 0U,
                                 NULL);

    passed += run_test("Null pointers",
                       test_number++,
                       CHECKSUM8_STATUS_INVALID_ARGUMENT,
                       status);

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
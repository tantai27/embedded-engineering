#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "buffer_copy.h"

#define BUFFER_SIZE       (8U)
#define TEST_CASE_COUNT   (9U)

static uint32_t run_test(const char * const test_name,
                         const uint32_t test_number,
                         const uint32_t expected,
                         const uint32_t actual)
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

static uint32_t buffers_equal(const uint8_t * const buffer_a,
                              const uint8_t * const buffer_b,
                              uint32_t length)
{
    uint32_t index = 0U;

    for (index = 0U; index < length; ++index)
    {
        if (buffer_a[index] != buffer_b[index])
        {
            return 0U;
        }
    }

    return 1U;
}

int main(void)
{
    const uint8_t source[BUFFER_SIZE] =
    {
        0x10U, 0x20U, 0x30U, 0x40U,
        0x50U, 0x60U, 0x70U, 0x80U
    };

    const uint8_t expected_full[BUFFER_SIZE] =
    {
        0x10U, 0x20U, 0x30U, 0x40U,
        0x50U, 0x60U, 0x70U, 0x80U
    };

    const uint8_t expected_partial[BUFFER_SIZE] =
    {
        0x00U, 0x00U, 0x10U, 0x20U,
        0x30U, 0x40U, 0x00U, 0x00U
    };

    uint8_t destination[BUFFER_SIZE] = {0U};
    uint8_t overlap_buffer[BUFFER_SIZE] =
    {
        0x10U, 0x20U, 0x30U, 0x40U,
        0x50U, 0x60U, 0x70U, 0x80U
    };

    uint32_t passed = 0U;
    uint32_t test_number = 1U;
    buffer_copy_status_t status;

    (void)printf("========================================\n");
    (void)printf("Running buffer_copy unit tests\n");
    (void)printf("========================================\n");

    status = buffer_copy(destination,
                         source,
                         BUFFER_SIZE);

    passed += run_test("Copy full buffer",
                       test_number++,
                       BUFFER_COPY_STATUS_SUCCESS,
                       status);

    passed += run_test("Verify full buffer",
                       test_number++,
                       1U,
                       buffers_equal(destination,
                                     expected_full,
                                     BUFFER_SIZE));

    destination[0] = 0U;
    destination[1] = 0U;
    destination[2] = 0U;
    destination[3] = 0U;
    destination[4] = 0U;
    destination[5] = 0U;
    destination[6] = 0U;
    destination[7] = 0U;

    status = buffer_copy(&destination[2],
                         source,
                         4U);

    passed += run_test("Copy partial buffer",
                       test_number++,
                       BUFFER_COPY_STATUS_SUCCESS,
                       status);

    passed += run_test("Verify partial buffer",
                       test_number++,
                       1U,
                       buffers_equal(destination,
                                     expected_partial,
                                     BUFFER_SIZE));

    status = buffer_copy(destination,
                         source,
                         0U);

    passed += run_test("Zero length copy",
                       test_number++,
                       BUFFER_COPY_STATUS_SUCCESS,
                       status);

    status = buffer_copy(NULL,
                         source,
                         4U);

    passed += run_test("Null destination",
                       test_number++,
                       BUFFER_COPY_STATUS_INVALID_ARGUMENT,
                       status);

    status = buffer_copy(destination,
                         NULL,
                         4U);

    passed += run_test("Null source",
                       test_number++,
                       BUFFER_COPY_STATUS_INVALID_ARGUMENT,
                       status);

    status = buffer_copy(NULL,
                         NULL,
                         4U);

    passed += run_test("Null source and destination",
                       test_number++,
                       BUFFER_COPY_STATUS_INVALID_ARGUMENT,
                       status);

    status = buffer_copy(&overlap_buffer[1],
                         &overlap_buffer[0],
                         4U);

    passed += run_test("Overlapping buffers",
                       test_number++,
                       BUFFER_COPY_STATUS_OVERLAP,
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
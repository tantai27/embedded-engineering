#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "memory_compare.h"

#define TEST_CASE_COUNT (8U)

typedef struct
{
    const char *name;
    const void *lhs;
    const void *rhs;
    uint32_t size;
    memory_compare_status_t expected_status;
} test_case_t;

static uint32_t run_test(const test_case_t * const test_case,
                         const uint32_t test_number)
{
    const memory_compare_status_t actual_status =
        memory_compare(test_case->lhs,
                       test_case->rhs,
                       test_case->size);

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
    static const uint8_t data_a[] =
    {
        0x10U, 0x20U, 0x30U, 0x40U
    };

    static const uint8_t data_b[] =
    {
        0x10U, 0x20U, 0x30U, 0x40U
    };

    static const uint8_t data_c[] =
    {
        0x10U, 0x20U, 0x30U, 0x50U
    };

    static const uint8_t data_d[] =
    {
        0x10U, 0x20U, 0x30U, 0x40U, 0x50U
    };

    static const test_case_t test_cases[] =
    {
        {
            "Equal memory regions",
            data_a,
            data_b,
            4U,
            MEMORY_COMPARE_STATUS_EQUAL
        },
        {
            "Different last byte",
            data_a,
            data_c,
            4U,
            MEMORY_COMPARE_STATUS_NOT_EQUAL
        },
        {
            "Different size ignored",
            data_a,
            data_d,
            4U,
            MEMORY_COMPARE_STATUS_EQUAL
        },
        {
            "Different first byte",
            data_c,
            data_b,
            4U,
            MEMORY_COMPARE_STATUS_NOT_EQUAL
        },
        {
            "Same pointer",
            data_a,
            data_a,
            4U,
            MEMORY_COMPARE_STATUS_EQUAL
        },
        {
            "Zero length",
            data_a,
            data_c,
            0U,
            MEMORY_COMPARE_STATUS_EQUAL
        },
        {
            "Null first pointer",
            NULL,
            data_b,
            4U,
            MEMORY_COMPARE_STATUS_INVALID_ARGUMENT
        },
        {
            "Null second pointer",
            data_a,
            NULL,
            4U,
            MEMORY_COMPARE_STATUS_INVALID_ARGUMENT
        }
    };

    uint32_t index = 0U;
    uint32_t passed = 0U;

    (void)printf("========================================\n");
    (void)printf("Running memory_compare unit tests\n");
    (void)printf("========================================\n");

    for (index = 0U; index < TEST_CASE_COUNT; ++index)
    {
        passed += run_test(&test_cases[index], index + 1U);
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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "linear_search.h"

#define TEST_CASE_COUNT (9U)

typedef struct
{
    const char *name;
    const uint32_t *arr;
    uint32_t size;
    uint32_t target;
    uint32_t expected_index;
    linear_search_status_t expected_status;
} test_case_t;

static uint32_t run_test(const test_case_t * const test_case,
                         const uint32_t test_number)
{
    uint32_t actual_index = 0U;
    const linear_search_status_t actual_status =
        linear_search(test_case->arr,
                      test_case->size,
                      test_case->target,
                      &actual_index);

    if ((actual_status == test_case->expected_status) &&
        ((LINEAR_SEARCH_STATUS_SUCCESS != actual_status) ||
         (actual_index == test_case->expected_index)))
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

    (void)printf("         Expected status: %u, Actual status: %u\n",
                 (uint32_t)test_case->expected_status,
                 (uint32_t)actual_status);

    if (LINEAR_SEARCH_STATUS_SUCCESS == test_case->expected_status)
    {
        (void)printf("         Expected index : %u, Actual index : %u\n",
                     test_case->expected_index,
                     actual_index);
    }

    return 0U;
}

int main(void)
{
    static const uint32_t sorted_array[] =
    {
        10U, 20U, 30U, 40U, 50U
    };

    static const uint32_t unsorted_array[] =
    {
        42U, 11U, 87U, 23U, 56U
    };

    static const uint32_t duplicate_array[] =
    {
        10U, 20U, 30U, 20U, 40U
    };

    static const uint32_t single_element_array[] =
    {
        55U
    };

    static const test_case_t test_cases[] =
    {
        {
            "First element",
            sorted_array,
            5U,
            10U,
            0U,
            LINEAR_SEARCH_STATUS_SUCCESS
        },
        {
            "Middle element",
            sorted_array,
            5U,
            30U,
            2U,
            LINEAR_SEARCH_STATUS_SUCCESS
        },
        {
            "Last element",
            sorted_array,
            5U,
            50U,
            4U,
            LINEAR_SEARCH_STATUS_SUCCESS
        },
        {
            "Target not found",
            sorted_array,
            5U,
            99U,
            0U,
            LINEAR_SEARCH_STATUS_NOT_FOUND
        },
        {
            "Unsorted array",
            unsorted_array,
            5U,
            23U,
            3U,
            LINEAR_SEARCH_STATUS_SUCCESS
        },
        {
            "First duplicate",
            duplicate_array,
            5U,
            20U,
            1U,
            LINEAR_SEARCH_STATUS_SUCCESS
        },
        {
            "Single element",
            single_element_array,
            1U,
            55U,
            0U,
            LINEAR_SEARCH_STATUS_SUCCESS
        },
        {
            "Null array",
            NULL,
            5U,
            10U,
            0U,
            LINEAR_SEARCH_STATUS_INVALID_ARGUMENT
        },
        {
            "Zero array size",
            sorted_array,
            0U,
            10U,
            0U,
            LINEAR_SEARCH_STATUS_INVALID_ARGUMENT
        }
    };

    uint32_t index = 0U;
    uint32_t passed = 0U;

    (void)printf("========================================\n");
    (void)printf("Running linear_search unit tests\n");
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
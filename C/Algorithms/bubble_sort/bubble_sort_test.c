#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "bubble_sort.h"

#define TEST_PASS          (0)
#define TEST_FAIL          (1)

#define TEST_CASE_COUNT    (12U)

typedef struct
{
    const char *name;
    int (*function)(void);
} test_case_t;

static uint32_t total_tests = 0U;
static uint32_t passed_tests = 0U;

static void report_test(const uint32_t test_number,
                        const uint32_t planned_tests,
                        const char *name,
                        const int result)
{
    ++total_tests;

    if (TEST_PASS == result)
    {
        ++passed_tests;
    }

    (void)printf("[%02u/%02u] %-30s [%s]\n",
                 test_number,
                 planned_tests,
                 name,
                 (TEST_PASS == result) ? "PASS" : "FAIL");
}

static int is_sorted_ascending(const uint32_t * const data,
                                const uint32_t length)
{
    uint32_t index = 0U;

    for (index = 0U; index < (length - 1U); ++index)
    {
        if (data[index] > data[index + 1U])
        {
            return TEST_FAIL;
        }
    }

    return TEST_PASS;
}

static int test_null_pointer(void)
{
    if (BUBBLE_SORT_STATUS_INVALID_ARGUMENT !=
        bubble_sort(NULL, 3U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_zero_length(void)
{
    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(NULL, 0U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_single_element(void)
{
    uint32_t data[] = {42U};

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 1U))
    {
        return TEST_FAIL;
    }

    if (42U != data[0])
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_already_sorted(void)
{
    uint32_t data[] =
    {
        1U, 2U, 3U, 4U, 5U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 5U))
    {
        return TEST_FAIL;
    }

    return is_sorted_ascending(data, 5U);
}

static int test_reverse_sorted(void)
{
    uint32_t data[] =
    {
        5U, 4U, 3U, 2U, 1U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 5U))
    {
        return TEST_FAIL;
    }

    return is_sorted_ascending(data, 5U);
}

static int test_random_values(void)
{
    uint32_t data[] =
    {
        42U, 7U, 19U, 3U, 88U, 15U, 1U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 7U))
    {
        return TEST_FAIL;
    }

    return is_sorted_ascending(data, 7U);
}

static int test_duplicate_values(void)
{
    uint32_t data[] =
    {
        4U, 2U, 4U, 1U, 2U, 4U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 6U))
    {
        return TEST_FAIL;
    }

    return is_sorted_ascending(data, 6U);
}

static int test_all_values_equal(void)
{
    uint32_t data[] =
    {
        7U, 7U, 7U, 7U, 7U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 5U))
    {
        return TEST_FAIL;
    }

    return is_sorted_ascending(data, 5U);
}

static int test_two_elements(void)
{
    uint32_t data[] =
    {
        2U, 1U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 2U))
    {
        return TEST_FAIL;
    }

    if ((1U != data[0]) ||
        (2U != data[1]))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_uint32_boundaries(void)
{
    uint32_t data[] =
    {
        UINT32_MAX,
        0U,
        UINT32_MAX - 1U,
        1U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 4U))
    {
        return TEST_FAIL;
    }

    if ((0U != data[0]) ||
        (1U != data[1]) ||
        ((UINT32_MAX - 1U) != data[2]) ||
        (UINT32_MAX != data[3]))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_mixed_duplicates_and_ordered_values(void)
{
    uint32_t data[] =
    {
        3U, 1U, 2U, 1U, 3U, 2U, 1U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 7U))
    {
        return TEST_FAIL;
    }

    if ((1U != data[0]) ||
        (1U != data[1]) ||
        (1U != data[2]) ||
        (2U != data[3]) ||
        (2U != data[4]) ||
        (3U != data[5]) ||
        (3U != data[6]))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_two_element_sorted_input(void)
{
    uint32_t data[] =
    {
        1U, 2U
    };

    if (BUBBLE_SORT_STATUS_SUCCESS !=
        bubble_sort(data, 2U))
    {
        return TEST_FAIL;
    }

    if ((1U != data[0]) ||
        (2U != data[1]))
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
            "NULL pointer",
            test_null_pointer
        },
        {
            "Zero length",
            test_zero_length
        },
        {
            "Single element",
            test_single_element
        },
        {
            "Already sorted",
            test_already_sorted
        },
        {
            "Reverse sorted",
            test_reverse_sorted
        },
        {
            "Random values",
            test_random_values
        },
        {
            "Duplicate values",
            test_duplicate_values
        },
        {
            "All values equal",
            test_all_values_equal
        },
        {
            "Two elements",
            test_two_elements
        },
        {
            "uint32 boundaries",
            test_uint32_boundaries
        },
        {
            "Mixed duplicates",
            test_mixed_duplicates_and_ordered_values
        },
        {
            "Two element sorted input",
            test_two_element_sorted_input
        }
    };

    uint32_t index = 0U;
    int result = TEST_PASS;

    (void)printf("========================================\n");
    (void)printf("Running bubble_sort unit tests\n");
    (void)printf("========================================\n");

    for (index = 0U; index < TEST_CASE_COUNT; ++index)
    {
        result = test_cases[index].function();

        report_test(index + 1U,
                    TEST_CASE_COUNT,
                    test_cases[index].name,
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
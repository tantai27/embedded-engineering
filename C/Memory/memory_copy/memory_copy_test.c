#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "memory_copy.h"

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

static int test_copy_normal(void)
{
    uint8_t src[]  = {1U, 2U, 3U, 4U};
    uint8_t dest[] = {0U, 0U, 0U, 0U};

    if (MEM_STATUS_SUCCESS != memory_copy(dest, src, sizeof(src)))
    {
        return TEST_FAIL;
    }

    if (0 != memcmp(dest, src, sizeof(src)))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_copy_zero_length(void)
{
    uint8_t src[]  = {1U, 2U};
    uint8_t dest[] = {3U, 4U};

    if (MEM_STATUS_SUCCESS != memory_copy(dest, src, 0U))
    {
        return TEST_FAIL;
    }

    if ((3U != dest[0]) || (4U != dest[1]))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_overlap_forward(void)
{
    uint8_t buffer[] = {1U, 2U, 3U, 4U, 5U};

    if (MEM_STATUS_SUCCESS != memory_copy(&buffer[1],
                                          &buffer[0],
                                          4U))
    {
        return TEST_FAIL;
    }

    const uint8_t expected[] = {1U, 1U, 2U, 3U, 4U};

    if (0 != memcmp(buffer, expected, sizeof(buffer)))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_overlap_backward(void)
{
    uint8_t buffer[] = {1U, 2U, 3U, 4U, 5U};

    if (MEM_STATUS_SUCCESS != memory_copy(&buffer[0],
                                          &buffer[1],
                                          4U))
    {
        return TEST_FAIL;
    }

    const uint8_t expected[] = {2U, 3U, 4U, 5U, 5U};

    if (0 != memcmp(buffer, expected, sizeof(buffer)))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_destination(void)
{
    uint8_t src[] = {1U};

    if (MEM_STATUS_INVALID_ARGUMENT !=
        memory_copy(NULL, src, sizeof(src)))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_source(void)
{
    uint8_t dest[] = {0U};

    if (MEM_STATUS_INVALID_ARGUMENT !=
        memory_copy(dest, NULL, sizeof(dest)))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static const test_case_t test_cases[] =
{
    { "Copy normal buffer",      test_copy_normal },
    { "Copy zero length",        test_copy_zero_length },
    { "Overlap forward copy",    test_overlap_forward },
    { "Overlap backward copy",   test_overlap_backward },
    { "Null destination",        test_null_destination },
    { "Null source",             test_null_source }
};

int main(void)
{
    const uint32_t planned_tests =
        (uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));

    (void)printf("========================================\n");
    (void)printf("Running memory_copy unit tests\n");
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
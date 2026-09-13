#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "event_flags.h"

#define TEST_PASS    (0)
#define TEST_FAIL    (1)

#define TEST_CASE_COUNT    (19U)

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
}

static int test_init_success(void)
{
    event_flags_t event_flags;

    event_flags.flags = 0xFFFFFFFFUL;

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_init(&event_flags))
    {
        return TEST_FAIL;
    }

    if (0U != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_init_invalid_argument(void)
{
    if (EVENT_FLAGS_STATUS_INVALID_ARGUMENT !=
        event_flags_init(NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_set_single_flag(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_set(&event_flags, 0x00000001UL))
    {
        return TEST_FAIL;
    }

    if (0x00000001UL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_set_multiple_flags(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_set(&event_flags, 0x00000005UL))
    {
        return TEST_FAIL;
    }

    if (0x00000005UL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_set(&event_flags, 0x0000000AUL))
    {
        return TEST_FAIL;
    }

    if (0x0000000FUL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_set_existing_flag(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x00000001UL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_set(&event_flags, 0x00000001UL))
    {
        return TEST_FAIL;
    }

    if (0x00000001UL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_set_all_flags(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_set(&event_flags, 0xFFFFFFFFUL))
    {
        return TEST_FAIL;
    }

    if (0xFFFFFFFFUL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_clear_single_flag(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x00000007UL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_clear(&event_flags, 0x00000002UL))
    {
        return TEST_FAIL;
    }

    if (0x00000005UL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_clear_multiple_flags(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x0000000FUL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_clear(&event_flags, 0x00000005UL))
    {
        return TEST_FAIL;
    }

    if (0x0000000AUL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_clear_unset_flag(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x00000005UL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_clear(&event_flags, 0x00000002UL))
    {
        return TEST_FAIL;
    }

    if (0x00000005UL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_clear_all_flags(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0xFFFFFFFFUL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_clear(&event_flags, 0xFFFFFFFFUL))
    {
        return TEST_FAIL;
    }

    if (0U != event_flags.flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_get_flags(void)
{
    event_flags_t event_flags;
    uint32_t flags = 0U;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x12345678UL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_get(&event_flags, &flags))
    {
        return TEST_FAIL;
    }

    if (0x12345678UL != flags)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_get_flags_invalid_arguments(void)
{
    event_flags_t event_flags;
    uint32_t flags = 0U;

    (void)event_flags_init(&event_flags);

    if (EVENT_FLAGS_STATUS_INVALID_ARGUMENT !=
        event_flags_get(NULL, &flags))
    {
        return TEST_FAIL;
    }

    if (EVENT_FLAGS_STATUS_INVALID_ARGUMENT !=
        event_flags_get(&event_flags, NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_are_set_all_requested_flags(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x0000000FUL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_are_set(
            &event_flags,
            0x00000005UL,
            &set))
    {
        return TEST_FAIL;
    }

    if (1U != set)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_are_set_partial_flags(void)
{
    event_flags_t event_flags;
    uint8_t set = 1U;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x00000005UL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_are_set(
            &event_flags,
            0x00000003UL,
            &set))
    {
        return TEST_FAIL;
    }

    if (0U != set)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_are_set_zero_mask(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_are_set(
            &event_flags,
            0U,
            &set))
    {
        return TEST_FAIL;
    }

    if (1U != set)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_are_set_all_flags(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0xFFFFFFFFUL);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_are_set(
            &event_flags,
            0xFFFFFFFFUL,
            &set))
    {
        return TEST_FAIL;
    }

    if (1U != set)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_are_set_invalid_arguments(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);

    if (EVENT_FLAGS_STATUS_INVALID_ARGUMENT !=
        event_flags_are_set(
            NULL,
            0x00000001UL,
            &set))
    {
        return TEST_FAIL;
    }

    if (EVENT_FLAGS_STATUS_INVALID_ARGUMENT !=
        event_flags_are_set(
            &event_flags,
            0x00000001UL,
            NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_arguments(void)
{
    if (EVENT_FLAGS_STATUS_INVALID_ARGUMENT !=
        event_flags_set(NULL, 0x00000001UL))
    {
        return TEST_FAIL;
    }

    if (EVENT_FLAGS_STATUS_INVALID_ARGUMENT !=
        event_flags_clear(NULL, 0x00000001UL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_boundary_bit_31(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_set(
            &event_flags,
            0x80000000UL))
    {
        return TEST_FAIL;
    }

    if (0x80000000UL != event_flags.flags)
    {
        return TEST_FAIL;
    }

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_are_set(
            &event_flags,
            0x80000000UL,
            &set))
    {
        return TEST_FAIL;
    }

    if (1U != set)
    {
        return TEST_FAIL;
    }

    if (EVENT_FLAGS_STATUS_SUCCESS !=
        event_flags_clear(
            &event_flags,
            0x80000000UL))
    {
        return TEST_FAIL;
    }

    if (0U != event_flags.flags)
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
            "Init success",
            test_init_success
        },
        {
            "Init invalid argument",
            test_init_invalid_argument
        },
        {
            "Set single flag",
            test_set_single_flag
        },
        {
            "Set multiple flags",
            test_set_multiple_flags
        },
        {
            "Set existing flag",
            test_set_existing_flag
        },
        {
            "Set all flags",
            test_set_all_flags
        },
        {
            "Clear single flag",
            test_clear_single_flag
        },
        {
            "Clear multiple flags",
            test_clear_multiple_flags
        },
        {
            "Clear unset flag",
            test_clear_unset_flag
        },
        {
            "Clear all flags",
            test_clear_all_flags
        },
        {
            "Get flags",
            test_get_flags
        },
        {
            "Get invalid arguments",
            test_get_flags_invalid_arguments
        },
        {
            "Are set all requested",
            test_are_set_all_requested_flags
        },
        {
            "Are set partial flags",
            test_are_set_partial_flags
        },
        {
            "Are set zero mask",
            test_are_set_zero_mask
        },
        {
            "Are set all flags",
            test_are_set_all_flags
        },
        {
            "Are set invalid arguments",
            test_are_set_invalid_arguments
        },
        {
            "Null arguments",
            test_null_arguments
        },
        {
            "Boundary bit 31",
            test_boundary_bit_31
        }
    };

    uint32_t index = 0U;
    int result = TEST_PASS;

    (void)printf("========================================\n");
    (void)printf("Running event_flags unit tests\n");
    (void)printf("========================================\n");

    for (index = 0U; index < TEST_CASE_COUNT; ++index)
    {
        result = test_cases[index].function();

        report_test(
            index + 1U,
            TEST_CASE_COUNT,
            test_cases[index].description,
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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "debounce.h"

#define TEST_PASS          (0)
#define TEST_FAIL          (1)

#define TEST_CASE_COUNT    (10U)

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

static int test_init_success(void)
{
    debounce_t debounce;

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_init(&debounce, 0U, 3U))
    {
        return TEST_FAIL;
    }

    if ((3U != debounce.stable_ticks) ||
        (0U != debounce.consecutive_ticks) ||
        (0U != debounce.stable_state) ||
        (0U != debounce.candidate_state))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_init_null_pointer(void)
{
    if (DEBOUNCE_STATUS_INVALID_ARGUMENT !=
        debounce_init(NULL, 0U, 3U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_init_zero_stable_ticks(void)
{
    debounce_t debounce;

    if (DEBOUNCE_STATUS_INVALID_ARGUMENT !=
        debounce_init(&debounce, 0U, 0U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_init_invalid_state(void)
{
    debounce_t debounce;

    if (DEBOUNCE_STATUS_INVALID_ARGUMENT !=
        debounce_init(&debounce, 2U, 3U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_stable_input_remains_unchanged(void)
{
    debounce_t debounce;
    uint8_t stable_state = 0U;

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_init(&debounce, 0U, 3U))
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 0U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (0U != stable_state)
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 0U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (0U != stable_state)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_state_changes_after_required_ticks(void)
{
    debounce_t debounce;
    uint8_t stable_state = 0U;

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_init(&debounce, 0U, 3U))
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 1U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (0U != stable_state)
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 1U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (0U != stable_state)
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 1U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (1U != stable_state)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_bouncing_input_does_not_change_state(void)
{
    debounce_t debounce;
    uint8_t stable_state = 0U;
    static const uint8_t raw_sequence[] =
    {
        1U, 0U, 1U, 0U, 1U, 0U, 1U
    };
    uint32_t index = 0U;

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_init(&debounce, 0U, 3U))
    {
        return TEST_FAIL;
    }

    for (index = 0U;
         index < (uint32_t)(sizeof(raw_sequence) /
                            sizeof(raw_sequence[0]));
         ++index)
    {
        if (DEBOUNCE_STATUS_SUCCESS !=
            debounce_update(&debounce,
                            raw_sequence[index],
                            &stable_state))
        {
            return TEST_FAIL;
        }

        if (0U != stable_state)
        {
            return TEST_FAIL;
        }
    }

    return TEST_PASS;
}

static int test_candidate_counter_resets_on_state_change(void)
{
    debounce_t debounce;
    uint8_t stable_state = 0U;

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_init(&debounce, 0U, 3U))
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 1U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (1U != debounce.consecutive_ticks)
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 1U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (2U != debounce.consecutive_ticks)
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 0U, &stable_state))
    {
        return TEST_FAIL;
    }

    if ((0U != debounce.consecutive_ticks) ||
        (0U != debounce.candidate_state))
    {
        return TEST_FAIL;
    }

    if (0U != stable_state)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_state_can_transition_back(void)
{
    debounce_t debounce;
    uint8_t stable_state = 0U;

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_init(&debounce, 0U, 2U))
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 1U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 1U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (1U != stable_state)
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 0U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (1U != stable_state)
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_update(&debounce, 0U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (0U != stable_state)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_update_null_arguments(void)
{
    debounce_t debounce;
    uint8_t stable_state = 0U;

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_init(&debounce, 0U, 3U))
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_INVALID_ARGUMENT !=
        debounce_update(NULL, 0U, &stable_state))
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_INVALID_ARGUMENT !=
        debounce_update(&debounce, 0U, NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_update_invalid_raw_state(void)
{
    debounce_t debounce;
    uint8_t stable_state = 0U;

    if (DEBOUNCE_STATUS_SUCCESS !=
        debounce_init(&debounce, 0U, 3U))
    {
        return TEST_FAIL;
    }

    if (DEBOUNCE_STATUS_INVALID_ARGUMENT !=
        debounce_update(&debounce, 2U, &stable_state))
    {
        return TEST_FAIL;
    }

    if ((0U != stable_state) ||
        (0U != debounce.consecutive_ticks))
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
            "Initialization success",
            test_init_success
        },
        {
            "Initialization NULL pointer",
            test_init_null_pointer
        },
        {
            "Initialization zero ticks",
            test_init_zero_stable_ticks
        },
        {
            "Initialization invalid state",
            test_init_invalid_state
        },
        {
            "Stable input unchanged",
            test_stable_input_remains_unchanged
        },
        {
            "Transition after required ticks",
            test_state_changes_after_required_ticks
        },
        {
            "Bouncing input filtered",
            test_bouncing_input_does_not_change_state
        },
        {
            "Candidate counter reset",
            test_candidate_counter_resets_on_state_change
        },
        {
            "State transition back",
            test_state_can_transition_back
        },
        {
            "Invalid update arguments",
            test_update_null_arguments
        }
    };

    uint32_t index = 0U;
    int result = TEST_PASS;

    (void)printf("========================================\n");
    (void)printf("Running debounce unit tests\n");
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
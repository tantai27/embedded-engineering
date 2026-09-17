#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "watchdog_simulator.h"

#define TEST_PASS    (0)
#define TEST_FAIL    (1)

#define TEST_CASE_COUNT    (10U)

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
    watchdog_simulator_t watchdog;

    if (WATCHDOG_SIMULATOR_STATUS_SUCCESS !=
        watchdog_simulator_init(&watchdog, 5U))
    {
        return TEST_FAIL;
    }

    if (5U != watchdog.timeout)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.running)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.expired)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_init_invalid_arguments(void)
{
    watchdog_simulator_t watchdog;

    if (WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT !=
        watchdog_simulator_init(NULL, 5U))
    {
        return TEST_FAIL;
    }

    if (WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT !=
        watchdog_simulator_init(&watchdog, 0U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_start(void)
{
    watchdog_simulator_t watchdog;

    (void)watchdog_simulator_init(&watchdog, 5U);

    if (WATCHDOG_SIMULATOR_STATUS_SUCCESS !=
        watchdog_simulator_start(&watchdog))
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (1U != watchdog.running)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.expired)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_tick_before_timeout(void)
{
    watchdog_simulator_t watchdog;

    (void)watchdog_simulator_init(&watchdog, 3U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);

    if (1U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (1U != watchdog.running)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.expired)
    {
        return TEST_FAIL;
    }

    (void)watchdog_simulator_tick(&watchdog);

    if (2U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (1U != watchdog.running)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.expired)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_expiration_at_timeout(void)
{
    watchdog_simulator_t watchdog;
    uint8_t expired = 0U;

    (void)watchdog_simulator_init(&watchdog, 3U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    if (3U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.running)
    {
        return TEST_FAIL;
    }

    if (1U != watchdog.expired)
    {
        return TEST_FAIL;
    }

    if (WATCHDOG_SIMULATOR_STATUS_SUCCESS !=
        watchdog_simulator_is_expired(&watchdog, &expired))
    {
        return TEST_FAIL;
    }

    if (1U != expired)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_feed(void)
{
    watchdog_simulator_t watchdog;

    (void)watchdog_simulator_init(&watchdog, 5U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    if (2U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (WATCHDOG_SIMULATOR_STATUS_SUCCESS !=
        watchdog_simulator_feed(&watchdog))
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (1U != watchdog.running)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.expired)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_feed_prevents_expiration(void)
{
    watchdog_simulator_t watchdog;
    uint8_t expired = 0U;

    (void)watchdog_simulator_init(&watchdog, 3U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    (void)watchdog_simulator_feed(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    if (WATCHDOG_SIMULATOR_STATUS_SUCCESS !=
        watchdog_simulator_is_expired(&watchdog, &expired))
    {
        return TEST_FAIL;
    }

    if (0U != expired)
    {
        return TEST_FAIL;
    }

    if (2U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (1U != watchdog.running)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_start_restarts_watchdog(void)
{
    watchdog_simulator_t watchdog;

    (void)watchdog_simulator_init(&watchdog, 2U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    if (1U != watchdog.expired)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.running)
    {
        return TEST_FAIL;
    }

    (void)watchdog_simulator_start(&watchdog);

    if (0U != watchdog.elapsed)
    {
        return TEST_FAIL;
    }

    if (1U != watchdog.running)
    {
        return TEST_FAIL;
    }

    if (0U != watchdog.expired)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_is_expired_invalid_arguments(void)
{
    watchdog_simulator_t watchdog;
    uint8_t expired = 0U;

    (void)watchdog_simulator_init(&watchdog, 5U);

    if (WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT !=
        watchdog_simulator_is_expired(NULL, &expired))
    {
        return TEST_FAIL;
    }

    if (WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT !=
        watchdog_simulator_is_expired(&watchdog, NULL))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_arguments(void)
{
    if (WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT !=
        watchdog_simulator_start(NULL))
    {
        return TEST_FAIL;
    }

    if (WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT !=
        watchdog_simulator_feed(NULL))
    {
        return TEST_FAIL;
    }

    if (WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT !=
        watchdog_simulator_tick(NULL))
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
            "Init invalid arguments",
            test_init_invalid_arguments
        },
        {
            "Start watchdog",
            test_start
        },
        {
            "Tick before timeout",
            test_tick_before_timeout
        },
        {
            "Expiration at timeout",
            test_expiration_at_timeout
        },
        {
            "Feed watchdog",
            test_feed
        },
        {
            "Feed prevents expiration",
            test_feed_prevents_expiration
        },
        {
            "Start restarts watchdog",
            test_start_restarts_watchdog
        },
        {
            "Is expired invalid arguments",
            test_is_expired_invalid_arguments
        },
        {
            "Null arguments",
            test_null_arguments
        }
    };

    uint32_t index = 0U;
    int result = TEST_PASS;

    (void)printf("========================================\n");
    (void)printf("Running watchdog_simulator unit tests\n");
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
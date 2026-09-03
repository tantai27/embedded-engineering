#include <stdio.h>
#include <stdint.h>

#include "watchdog_simulator.h"

static uint32_t tests_run = 0U;
static uint32_t tests_passed = 0U;

#define TEST_ASSERT(condition)                                      \
    do                                                              \
    {                                                               \
        ++tests_run;                                                \
        if (condition)                                              \
        {                                                           \
            ++tests_passed;                                         \
        }                                                           \
        else                                                        \
        {                                                           \
            printf("FAIL: %s:%u\n", __FILE__, __LINE__);            \
        }                                                           \
    } while (0)

static void test_init_success(void)
{
    watchdog_simulator_t watchdog;

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_SUCCESS ==
        watchdog_simulator_init(&watchdog, 5U));

    TEST_ASSERT(5U == watchdog.timeout);
    TEST_ASSERT(0U == watchdog.elapsed);
    TEST_ASSERT(0U == watchdog.running);
    TEST_ASSERT(0U == watchdog.expired);
}

static void test_init_invalid_arguments(void)
{
    watchdog_simulator_t watchdog;

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT ==
        watchdog_simulator_init(NULL, 5U));

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT ==
        watchdog_simulator_init(&watchdog, 0U));
}

static void test_start(void)
{
    watchdog_simulator_t watchdog;

    (void)watchdog_simulator_init(&watchdog, 5U);

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_SUCCESS ==
        watchdog_simulator_start(&watchdog));

    TEST_ASSERT(0U == watchdog.elapsed);
    TEST_ASSERT(1U == watchdog.running);
    TEST_ASSERT(0U == watchdog.expired);
}

static void test_tick_before_timeout(void)
{
    watchdog_simulator_t watchdog;

    (void)watchdog_simulator_init(&watchdog, 3U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);

    TEST_ASSERT(1U == watchdog.elapsed);
    TEST_ASSERT(1U == watchdog.running);
    TEST_ASSERT(0U == watchdog.expired);

    (void)watchdog_simulator_tick(&watchdog);

    TEST_ASSERT(2U == watchdog.elapsed);
    TEST_ASSERT(1U == watchdog.running);
    TEST_ASSERT(0U == watchdog.expired);
}

static void test_expiration_at_timeout(void)
{
    watchdog_simulator_t watchdog;
    uint8_t expired = 0U;

    (void)watchdog_simulator_init(&watchdog, 3U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    TEST_ASSERT(3U == watchdog.elapsed);
    TEST_ASSERT(0U == watchdog.running);
    TEST_ASSERT(1U == watchdog.expired);

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_SUCCESS ==
        watchdog_simulator_is_expired(&watchdog, &expired));

    TEST_ASSERT(1U == expired);
}

static void test_feed(void)
{
    watchdog_simulator_t watchdog;

    (void)watchdog_simulator_init(&watchdog, 5U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    TEST_ASSERT(2U == watchdog.elapsed);

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_SUCCESS ==
        watchdog_simulator_feed(&watchdog));

    TEST_ASSERT(0U == watchdog.elapsed);
    TEST_ASSERT(1U == watchdog.running);
    TEST_ASSERT(0U == watchdog.expired);
}

static void test_feed_prevents_expiration(void)
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

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_SUCCESS ==
        watchdog_simulator_is_expired(&watchdog, &expired));

    TEST_ASSERT(0U == expired);
    TEST_ASSERT(2U == watchdog.elapsed);
    TEST_ASSERT(1U == watchdog.running);
}

static void test_start_restarts_watchdog(void)
{
    watchdog_simulator_t watchdog;

    (void)watchdog_simulator_init(&watchdog, 2U);
    (void)watchdog_simulator_start(&watchdog);

    (void)watchdog_simulator_tick(&watchdog);
    (void)watchdog_simulator_tick(&watchdog);

    TEST_ASSERT(1U == watchdog.expired);
    TEST_ASSERT(0U == watchdog.running);

    (void)watchdog_simulator_start(&watchdog);

    TEST_ASSERT(0U == watchdog.elapsed);
    TEST_ASSERT(1U == watchdog.running);
    TEST_ASSERT(0U == watchdog.expired);
}

static void test_is_expired_invalid_arguments(void)
{
    watchdog_simulator_t watchdog;
    uint8_t expired = 0U;

    (void)watchdog_simulator_init(&watchdog, 5U);

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT ==
        watchdog_simulator_is_expired(NULL, &expired));

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT ==
        watchdog_simulator_is_expired(&watchdog, NULL));
}

static void test_null_arguments(void)
{
    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT ==
        watchdog_simulator_start(NULL));

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT ==
        watchdog_simulator_feed(NULL));

    TEST_ASSERT(
        WATCHDOG_SIMULATOR_STATUS_INVALID_ARGUMENT ==
        watchdog_simulator_tick(NULL));
}

int main(void)
{
    test_init_success();
    test_init_invalid_arguments();
    test_start();
    test_tick_before_timeout();
    test_expiration_at_timeout();
    test_feed();
    test_feed_prevents_expiration();
    test_start_restarts_watchdog();
    test_is_expired_invalid_arguments();
    test_null_arguments();

    printf("Tests: %u, Passed: %u, Failed: %u\n",
           tests_run,
           tests_passed,
           tests_run - tests_passed);

    return (tests_run == tests_passed) ? 0 : 1;
}
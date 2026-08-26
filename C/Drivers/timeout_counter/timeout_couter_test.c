#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "timeout_counter.h"

#define TIMEOUT_VALUE       (3U)
#define TEST_CASE_COUNT     (10U)

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

static uint32_t run_expired_test(const char * const test_name,
                                 const uint32_t test_number,
                                 const uint8_t expected,
                                 const timeout_counter_t * const counter)
{
    uint8_t expired = 0U;
    timeout_counter_status_t status;

    status = timeout_counter_is_expired(counter, &expired);

    if ((TIMEOUT_COUNTER_STATUS_SUCCESS == status) &&
        (expected == expired))
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
                 (uint32_t)expected,
                 (uint32_t)expired);

    return 0U;
}

int main(void)
{
    timeout_counter_t counter;
    timeout_counter_status_t status;
    uint32_t passed = 0U;
    uint32_t test_number = 1U;

    (void)printf("========================================\n");
    (void)printf("Running timeout_counter unit tests\n");
    (void)printf("========================================\n");

    status = timeout_counter_init(&counter,
                                  TIMEOUT_VALUE);

    passed += run_test("Timeout initialization",
                       test_number++,
                       TIMEOUT_COUNTER_STATUS_SUCCESS,
                       status);

    passed += run_test("Initial elapsed value",
                       test_number++,
                       0U,
                       counter.elapsed);

    passed += run_expired_test("Initial timeout state",
                               test_number++,
                               0U,
                               &counter);

    status = timeout_counter_start(&counter);

    passed += run_test("Start timeout",
                       test_number++,
                       TIMEOUT_COUNTER_STATUS_SUCCESS,
                       status);

    status = timeout_counter_tick(&counter);

    passed += run_test("First tick",
                       test_number++,
                       TIMEOUT_COUNTER_STATUS_SUCCESS,
                       status);

    passed += run_test("Elapsed after first tick",
                       test_number++,
                       1U,
                       counter.elapsed);

    status = timeout_counter_tick(&counter);
    status = timeout_counter_tick(&counter);

    passed += run_test("Reach timeout boundary",
                       test_number++,
                       TIMEOUT_COUNTER_STATUS_SUCCESS,
                       status);

    passed += run_expired_test("Timeout expired",
                               test_number++,
                               1U,
                               &counter);

    status = timeout_counter_start(&counter);

    passed += run_test("Restart timeout",
                       test_number++,
                       TIMEOUT_COUNTER_STATUS_SUCCESS,
                       status);

    passed += run_test("Elapsed reset after restart",
                       test_number++,
                       0U,
                       counter.elapsed);

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
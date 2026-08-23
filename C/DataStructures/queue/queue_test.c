#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "queue.h"

#define QUEUE_CAPACITY    (3U)
#define TEST_CASE_COUNT   (10U)

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

int main(void)
{
    uint32_t buffer[QUEUE_CAPACITY];
    uint32_t data = 0U;
    uint32_t passed = 0U;
    uint32_t test_number = 1U;
    queue_t queue;
    queue_status_t status;

    (void)printf("========================================\n");
    (void)printf("Running queue unit tests\n");
    (void)printf("========================================\n");

    status = queue_init(&queue,
                        buffer,
                        QUEUE_CAPACITY);

    passed += run_test("Queue initialization",
                       test_number++,
                       QUEUE_STATUS_SUCCESS,
                       status);

    status = queue_init(NULL,
                        buffer,
                        QUEUE_CAPACITY);

    passed += run_test("Null queue initialization",
                       test_number++,
                       QUEUE_STATUS_INVALID_ARGUMENT,
                       status);

    status = queue_init(&queue,
                        NULL,
                        QUEUE_CAPACITY);

    passed += run_test("Null buffer initialization",
                       test_number++,
                       QUEUE_STATUS_INVALID_ARGUMENT,
                       status);

    status = queue_init(&queue,
                        buffer,
                        0U);

    passed += run_test("Zero capacity initialization",
                       test_number++,
                       QUEUE_STATUS_INVALID_ARGUMENT,
                       status);

    (void)queue_init(&queue,
                     buffer,
                     QUEUE_CAPACITY);

    status = queue_push(&queue, 10U);
    passed += run_test("Push first element",
                       test_number++,
                       QUEUE_STATUS_SUCCESS,
                       status);

    status = queue_push(&queue, 20U);
    passed += run_test("Push second element",
                       test_number++,
                       QUEUE_STATUS_SUCCESS,
                       status);

    status = queue_push(&queue, 30U);
    passed += run_test("Push third element",
                       test_number++,
                       QUEUE_STATUS_SUCCESS,
                       status);

    status = queue_push(&queue, 40U);
    passed += run_test("Full queue detection",
                       test_number++,
                       QUEUE_STATUS_FULL,
                       status);

    status = queue_pop(&queue, &data);

    if ((QUEUE_STATUS_SUCCESS == status) && (10U == data))
    {
        passed += run_test("FIFO first element",
                           test_number,
                           1U,
                           1U);
    }
    else
    {
        passed += run_test("FIFO first element",
                           test_number,
                           10U,
                           data);
    }

    ++test_number;

    status = queue_pop(&queue, &data);

    if ((QUEUE_STATUS_SUCCESS == status) && (20U == data))
    {
        passed += run_test("FIFO second element",
                           test_number,
                           1U,
                           1U);
    }
    else
    {
        passed += run_test("FIFO second element",
                           test_number,
                           20U,
                           data);
    }

    ++test_number;

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
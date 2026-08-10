#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ring_buffer.h"

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

static int test_init(void)
{
uint8_t buffer[4U];
ring_buffer_t rb;


if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_init(&rb, buffer, 4U))
{
    return TEST_FAIL;
}

if ((0U != rb.read_index) ||
    (0U != rb.write_index) ||
    (0U != rb.count) ||
    (4U != rb.capacity))
{
    return TEST_FAIL;
}

if (buffer != rb.buffer)
{
    return TEST_FAIL;
}

return TEST_PASS;


}

static int test_init_invalid_argument(void)
{
uint8_t buffer[4U];
ring_buffer_t rb;


if (RING_BUFFER_STATUS_INVALID_ARGUMENT !=
    ring_buffer_init(NULL, buffer, 4U))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_INVALID_ARGUMENT !=
    ring_buffer_init(&rb, NULL, 4U))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_INVALID_ARGUMENT !=
    ring_buffer_init(&rb, buffer, 0U))
{
    return TEST_FAIL;
}

return TEST_PASS;


}

static int test_push_and_pop(void)
{
uint8_t buffer[4U];
uint8_t data = 0U;
ring_buffer_t rb;


if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_init(&rb, buffer, 4U))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_push(&rb, 0x11U))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_pop(&rb, &data))
{
    return TEST_FAIL;
}

if (0x11U != data)
{
    return TEST_FAIL;
}

return TEST_PASS;


}

static int test_fifo_order(void)
{
uint8_t buffer[4U];
uint8_t data = 0U;
ring_buffer_t rb;


if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_init(&rb, buffer, 4U))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x10U)) ||
    (RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x20U)) ||
    (RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x30U)))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_pop(&rb, &data)) ||
    (0x10U != data))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_pop(&rb, &data)) ||
    (0x20U != data))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_pop(&rb, &data)) ||
    (0x30U != data))
{
    return TEST_FAIL;
}

return TEST_PASS;


}

static int test_full_buffer(void)
{
uint8_t buffer[3U];
ring_buffer_t rb;


if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_init(&rb, buffer, 3U))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x01U)) ||
    (RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x02U)) ||
    (RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x03U)))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_FULL !=
    ring_buffer_push(&rb, 0x04U))
{
    return TEST_FAIL;
}

if (3U != rb.count)
{
    return TEST_FAIL;
}

return TEST_PASS;


}

static int test_empty_buffer(void)
{
uint8_t buffer[4U];
uint8_t data = 0U;
ring_buffer_t rb;


if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_init(&rb, buffer, 4U))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_EMPTY !=
    ring_buffer_pop(&rb, &data))
{
    return TEST_FAIL;
}

if (0U != rb.count)
{
    return TEST_FAIL;
}

return TEST_PASS;


}

static int test_wraparound(void)
{
uint8_t buffer[3U];
uint8_t data = 0U;
ring_buffer_t rb;


if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_init(&rb, buffer, 3U))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x11U)) ||
    (RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x22U)) ||
    (RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_push(&rb, 0x33U)))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_pop(&rb, &data)) ||
    (0x11U != data))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_push(&rb, 0x44U))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_pop(&rb, &data)) ||
    (0x22U != data))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_pop(&rb, &data)) ||
    (0x33U != data))
{
    return TEST_FAIL;
}

if ((RING_BUFFER_STATUS_SUCCESS !=
     ring_buffer_pop(&rb, &data)) ||
    (0x44U != data))
{
    return TEST_FAIL;
}

return TEST_PASS;


}

static int test_push_invalid_argument(void)
{
if (RING_BUFFER_STATUS_INVALID_ARGUMENT !=
ring_buffer_push(NULL, 0x55U))
{
return TEST_FAIL;
}


return TEST_PASS;


}

static int test_pop_invalid_argument(void)
{
uint8_t buffer[4U];
uint8_t data = 0U;
ring_buffer_t rb;


if (RING_BUFFER_STATUS_SUCCESS !=
    ring_buffer_init(&rb, buffer, 4U))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_INVALID_ARGUMENT !=
    ring_buffer_pop(NULL, &data))
{
    return TEST_FAIL;
}

if (RING_BUFFER_STATUS_INVALID_ARGUMENT !=
    ring_buffer_pop(&rb, NULL))
{
    return TEST_FAIL;
}

return TEST_PASS;


}

static const test_case_t test_cases[] =
{
{ "Initialize ring buffer",       test_init },
{ "Invalid initialization",       test_init_invalid_argument },
{ "Push and pop",                 test_push_and_pop },
{ "FIFO order",                   test_fifo_order },
{ "Full buffer",                  test_full_buffer },
{ "Empty buffer",                 test_empty_buffer },
{ "Index wraparound",             test_wraparound },
{ "Invalid push argument",        test_push_invalid_argument },
{ "Invalid pop argument",         test_pop_invalid_argument }
};

int main(void)
{
const uint32_t planned_tests =
(uint32_t)(sizeof(test_cases) / sizeof(test_cases[0]));


(void)printf("========================================\n");
(void)printf("Running ring_buffer unit tests\n");
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

return (failed_tests == 0U) ? EXIT_SUCCESS : EXIT_FAILURE;


}

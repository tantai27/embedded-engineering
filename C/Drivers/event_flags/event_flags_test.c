#include <stdio.h>
#include <stdint.h>

#include "event_flags.h"

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
    event_flags_t event_flags;

    event_flags.flags = 0xFFFFFFFFUL;

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_init(&event_flags));

    TEST_ASSERT(0U == event_flags.flags);
}

static void test_init_invalid_argument(void)
{
    TEST_ASSERT(
        EVENT_FLAGS_STATUS_INVALID_ARGUMENT ==
        event_flags_init(NULL));
}

static void test_set_single_flag(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_set(&event_flags, 0x00000001UL));

    TEST_ASSERT(0x00000001UL == event_flags.flags);
}

static void test_set_multiple_flags(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_set(&event_flags, 0x00000005UL));

    TEST_ASSERT(0x00000005UL == event_flags.flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_set(&event_flags, 0x0000000AUL));

    TEST_ASSERT(0x0000000FUL == event_flags.flags);
}

static void test_set_existing_flag(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    (void)event_flags_set(&event_flags, 0x00000001UL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_set(&event_flags, 0x00000001UL));

    TEST_ASSERT(0x00000001UL == event_flags.flags);
}

static void test_set_all_flags(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_set(&event_flags, 0xFFFFFFFFUL));

    TEST_ASSERT(0xFFFFFFFFUL == event_flags.flags);
}

static void test_clear_single_flag(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    (void)event_flags_set(&event_flags, 0x00000007UL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_clear(&event_flags, 0x00000002UL));

    TEST_ASSERT(0x00000005UL == event_flags.flags);
}

static void test_clear_multiple_flags(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    (void)event_flags_set(&event_flags, 0x0000000FUL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_clear(&event_flags, 0x00000005UL));

    TEST_ASSERT(0x0000000AUL == event_flags.flags);
}

static void test_clear_unset_flag(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    (void)event_flags_set(&event_flags, 0x00000005UL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_clear(&event_flags, 0x00000002UL));

    TEST_ASSERT(0x00000005UL == event_flags.flags);
}

static void test_clear_all_flags(void)
{
    event_flags_t event_flags;

    (void)event_flags_init(&event_flags);

    (void)event_flags_set(&event_flags, 0xFFFFFFFFUL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_clear(&event_flags, 0xFFFFFFFFUL));

    TEST_ASSERT(0U == event_flags.flags);
}

static void test_get_flags(void)
{
    event_flags_t event_flags;
    uint32_t flags = 0U;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x12345678UL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_get(&event_flags, &flags));

    TEST_ASSERT(0x12345678UL == flags);
}

static void test_get_flags_invalid_arguments(void)
{
    event_flags_t event_flags;
    uint32_t flags = 0U;

    (void)event_flags_init(&event_flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_INVALID_ARGUMENT ==
        event_flags_get(NULL, &flags));

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_INVALID_ARGUMENT ==
        event_flags_get(&event_flags, NULL));
}

static void test_are_set_all_requested_flags(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x0000000FUL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_are_set(&event_flags, 0x00000005UL, &set));

    TEST_ASSERT(1U == set);
}

static void test_are_set_partial_flags(void)
{
    event_flags_t event_flags;
    uint8_t set = 1U;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0x00000005UL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_are_set(&event_flags, 0x00000003UL, &set));

    TEST_ASSERT(0U == set);
}

static void test_are_set_zero_mask(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_are_set(&event_flags, 0U, &set));

    TEST_ASSERT(1U == set);
}

static void test_are_set_all_flags(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);
    (void)event_flags_set(&event_flags, 0xFFFFFFFFUL);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_are_set(&event_flags, 0xFFFFFFFFUL, &set));

    TEST_ASSERT(1U == set);
}

static void test_are_set_invalid_arguments(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_INVALID_ARGUMENT ==
        event_flags_are_set(NULL, 0x00000001UL, &set));

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_INVALID_ARGUMENT ==
        event_flags_are_set(&event_flags, 0x00000001UL, NULL));
}

static void test_null_arguments(void)
{
    TEST_ASSERT(
        EVENT_FLAGS_STATUS_INVALID_ARGUMENT ==
        event_flags_set(NULL, 0x00000001UL));

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_INVALID_ARGUMENT ==
        event_flags_clear(NULL, 0x00000001UL));
}

static void test_boundary_bit_31(void)
{
    event_flags_t event_flags;
    uint8_t set = 0U;

    (void)event_flags_init(&event_flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_set(&event_flags, 0x80000000UL));

    TEST_ASSERT(0x80000000UL == event_flags.flags);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_are_set(
            &event_flags,
            0x80000000UL,
            &set));

    TEST_ASSERT(1U == set);

    TEST_ASSERT(
        EVENT_FLAGS_STATUS_SUCCESS ==
        event_flags_clear(
            &event_flags,
            0x80000000UL));

    TEST_ASSERT(0U == event_flags.flags);
}

int main(void)
{
    test_init_success();
    test_init_invalid_argument();

    test_set_single_flag();
    test_set_multiple_flags();
    test_set_existing_flag();
    test_set_all_flags();

    test_clear_single_flag();
    test_clear_multiple_flags();
    test_clear_unset_flag();
    test_clear_all_flags();

    test_get_flags();
    test_get_flags_invalid_arguments();

    test_are_set_all_requested_flags();
    test_are_set_partial_flags();
    test_are_set_zero_mask();
    test_are_set_all_flags();
    test_are_set_invalid_arguments();

    test_null_arguments();
    test_boundary_bit_31();

    printf("Tests: %u, Passed: %u, Failed: %u\n",
           tests_run,
           tests_passed,
           tests_run - tests_passed);

    return (tests_run == tests_passed) ? 0 : 1;
}
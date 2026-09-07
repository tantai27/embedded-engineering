#include <stdio.h>
#include <stdint.h>

#include "bit_rotate.h"

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

static void test_rotate_left_zero(void)
{
    TEST_ASSERT(0xA5U == bit_rotate_left(0xA5U, 0U));
}

static void test_rotate_left_one(void)
{
    TEST_ASSERT(0x4BU == bit_rotate_left(0xA5U, 1U));
}

static void test_rotate_left_multiple(void)
{
    TEST_ASSERT(0x2DU == bit_rotate_left(0xA5U, 3U));
}

static void test_rotate_left_full_width(void)
{
    TEST_ASSERT(0xA5U == bit_rotate_left(0xA5U, 8U));
}

static void test_rotate_left_normalized_shift(void)
{
    TEST_ASSERT(0x4BU == bit_rotate_left(0xA5U, 9U));
}

static void test_rotate_left_all_zero(void)
{
    TEST_ASSERT(0x00U == bit_rotate_left(0x00U, 4U));
}

static void test_rotate_left_all_one(void)
{
    TEST_ASSERT(0xFFU == bit_rotate_left(0xFFU, 4U));
}

static void test_rotate_right_zero(void)
{
    TEST_ASSERT(0xA5U == bit_rotate_right(0xA5U, 0U));
}

static void test_rotate_right_one(void)
{
    TEST_ASSERT(0xD2U == bit_rotate_right(0xA5U, 1U));
}

static void test_rotate_right_multiple(void)
{
    TEST_ASSERT(0xB4U == bit_rotate_right(0xA5U, 3U));
}

static void test_rotate_right_full_width(void)
{
    TEST_ASSERT(0xA5U == bit_rotate_right(0xA5U, 8U));
}

static void test_rotate_right_normalized_shift(void)
{
    TEST_ASSERT(0xD2U == bit_rotate_right(0xA5U, 9U));
}

static void test_rotate_right_all_zero(void)
{
    TEST_ASSERT(0x00U == bit_rotate_right(0x00U, 4U));
}

static void test_rotate_right_all_one(void)
{
    TEST_ASSERT(0xFFU == bit_rotate_right(0xFFU, 4U));
}

static void test_rotate_inverse(void)
{
    uint8_t value = 0x96U;
    uint8_t rotated = 0U;

    rotated = bit_rotate_left(value, 3U);
    rotated = bit_rotate_right(rotated, 3U);

    TEST_ASSERT(value == rotated);
}

int main(void)
{
    test_rotate_left_zero();
    test_rotate_left_one();
    test_rotate_left_multiple();
    test_rotate_left_full_width();
    test_rotate_left_normalized_shift();
    test_rotate_left_all_zero();
    test_rotate_left_all_one();

    test_rotate_right_zero();
    test_rotate_right_one();
    test_rotate_right_multiple();
    test_rotate_right_full_width();
    test_rotate_right_normalized_shift();
    test_rotate_right_all_zero();
    test_rotate_right_all_one();

    test_rotate_inverse();

    printf("Tests: %u, Passed: %u, Failed: %u\n",
           tests_run,
           tests_passed,
           tests_run - tests_passed);

    return (tests_run == tests_passed) ? 0 : 1;
}
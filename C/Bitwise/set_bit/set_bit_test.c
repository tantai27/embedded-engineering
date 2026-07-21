#include <stdio.h>
#include <stdint.h>

#include "set_bit.h"

#define TEST_PASS    (0)
#define TEST_FAIL    (1)

static int test_set_bit_0(void)
{
    uint32_t reg = 0U;

    if (STATUS_SUCCESS != set_bit(&reg, 0U))
    {
        return TEST_FAIL;
    }

    if (0x00000001UL != reg)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_set_bit_31(void)
{
    uint32_t reg = 0U;

    if (STATUS_SUCCESS != set_bit(&reg, 31U))
    {
        return TEST_FAIL;
    }

    if (0x80000000UL != reg)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_set_bit_already_set(void)
{
    uint32_t reg = 0x00000008UL;

    if (STATUS_SUCCESS != set_bit(&reg, 3U))
    {
        return TEST_FAIL;
    }

    if (0x00000008UL != reg)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_set_bit_non_zero_register(void)
{
    uint32_t reg = 0xAAAAAAAAUL;

    if (STATUS_SUCCESS != set_bit(&reg, 0U))
    {
        return TEST_FAIL;
    }

    if (0xAAAAAAABUL != reg)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_null_pointer(void)
{
    if (STATUS_INVALID_ARGUMENT != set_bit(NULL, 5U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

static int test_invalid_bit(void)
{
    uint32_t reg = 0U;

    if (STATUS_INVALID_ARGUMENT != set_bit(&reg, 32U))
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

int main(void)
{
    (void)printf("test_set_bit_0                : %s\n",
                 (TEST_PASS == test_set_bit_0()) ? "PASS" : "FAIL");

    (void)printf("test_set_bit_31               : %s\n",
                 (TEST_PASS == test_set_bit_31()) ? "PASS" : "FAIL");

    (void)printf("test_set_bit_already_set      : %s\n",
                 (TEST_PASS == test_set_bit_already_set()) ? "PASS" : "FAIL");

    (void)printf("test_set_bit_non_zero_register: %s\n",
                 (TEST_PASS == test_set_bit_non_zero_register()) ? "PASS" : "FAIL");

    (void)printf("test_null_pointer             : %s\n",
                 (TEST_PASS == test_null_pointer()) ? "PASS" : "FAIL");

    (void)printf("test_invalid_bit              : %s\n",
                 (TEST_PASS == test_invalid_bit()) ? "PASS" : "FAIL");

    return 0;
}
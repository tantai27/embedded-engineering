#include <stdint.h>

#include "parentheses_validator.h"

#define PARENTHESES_STACK_CAPACITY (32U)

static uint8_t is_opening_bracket(const char bracket)
{
    uint8_t result = 0U;

    if (('(' == bracket) ||
        ('[' == bracket) ||
        ('{' == bracket))
    {
        result = 1U;
    }

    return result;
}

static uint8_t is_closing_bracket(const char bracket)
{
    uint8_t result = 0U;

    if ((')' == bracket) ||
        (']' == bracket) ||
        ('}' == bracket))
    {
        result = 1U;
    }

    return result;
}

static uint8_t brackets_match(const char opening,
                              const char closing)
{
    uint8_t result = 0U;

    if ((('(' == opening) && (')' == closing)) ||
        (('[' == opening) && (']' == closing)) ||
        (('{' == opening) && ('}' == closing)))
    {
        result = 1U;
    }

    return result;
}

parentheses_status_t parentheses_validate(const char * const str)
{
    char stack[PARENTHESES_STACK_CAPACITY];
    uint32_t top = 0U;
    const char *ptr = NULL;

    if (NULL == str)
    {
        return PARENTHESES_STATUS_INVALID_ARGUMENT;
    }

    ptr = str;

    while ('\0' != *ptr)
    {
        if (1U == is_opening_bracket(*ptr))
        {
            if (PARENTHESES_STACK_CAPACITY == top)
            {
                return PARENTHESES_STATUS_OVERFLOW;
            }

            stack[top] = *ptr;
            ++top;
        }
        else if (1U == is_closing_bracket(*ptr))
        {
            if (0U == top)
            {
                return PARENTHESES_STATUS_INVALID;
            }

            --top;

            if (1U != brackets_match(stack[top], *ptr))
            {
                return PARENTHESES_STATUS_INVALID;
            }
        }

        ++ptr;
    }

    if (0U != top)
    {
        return PARENTHESES_STATUS_INVALID;
    }

    return PARENTHESES_STATUS_VALID;
}
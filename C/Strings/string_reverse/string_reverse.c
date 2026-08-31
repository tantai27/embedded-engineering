#include <stddef.h>

#include "string_reverse.h"

string_reverse_status_t string_reverse(
    char * const string)
{
    uint32_t length = 0U;
    uint32_t left = 0U;
    uint32_t right = 0U;
    char temp;

    if (NULL == string)
    {
        return STRING_REVERSE_STATUS_INVALID_ARGUMENT;
    }

    while ('\0' != string[length])
    {
        ++length;
    }

    if (0U == length)
    {
        return STRING_REVERSE_STATUS_SUCCESS;
    }

    right = length - 1U;

    while (left < right)
    {
        temp = string[left];
        string[left] = string[right];
        string[right] = temp;

        ++left;
        --right;
    }

    return STRING_REVERSE_STATUS_SUCCESS;
}
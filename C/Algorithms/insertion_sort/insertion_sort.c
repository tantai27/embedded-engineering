#include <stddef.h>

#include "insertion_sort.h"

insertion_sort_status_t insertion_sort(
    uint32_t * const data,
    uint32_t length)
{
    uint32_t index = 0U;
    uint32_t position = 0U;
    uint32_t value = 0U;

    if ((NULL == data) && (0U != length))
    {
        return INSERTION_SORT_STATUS_INVALID_ARGUMENT;
    }

    if (length < 2U)
    {
        return INSERTION_SORT_STATUS_SUCCESS;
    }

    for (index = 1U; index < length; ++index)
    {
        value = data[index];
        position = index;

        while ((position > 0U) &&
               (data[position - 1U] > value))
        {
            data[position] = data[position - 1U];
            --position;
        }

        data[position] = value;
    }

    return INSERTION_SORT_STATUS_SUCCESS;
}
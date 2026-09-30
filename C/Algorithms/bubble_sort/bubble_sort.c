#include <stddef.h>

#include "bubble_sort.h"

bubble_sort_status_t bubble_sort(
    uint32_t * const data,
    uint32_t length)
{
    uint32_t pass = 0U;
    uint32_t index = 0U;
    uint32_t temp = 0U;
    uint8_t swapped = 0U;

    if ((NULL == data) && (0U != length))
    {
        return BUBBLE_SORT_STATUS_INVALID_ARGUMENT;
    }

    if (length < 2U)
    {
        return BUBBLE_SORT_STATUS_SUCCESS;
    }

    for (pass = 0U; pass < (length - 1U); ++pass)
    {
        swapped = 0U;

        for (index = 0U; index < (length - 1U - pass); ++index)
        {
            if (data[index] > data[index + 1U])
            {
                temp = data[index];
                data[index] = data[index + 1U];
                data[index + 1U] = temp;

                swapped = 1U;
            }
        }

        if (0U == swapped)
        {
            break;
        }
    }

    return BUBBLE_SORT_STATUS_SUCCESS;
}
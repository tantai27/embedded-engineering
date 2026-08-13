#include <stddef.h>

#include "crc8.h"

#define CRC8_POLYNOMIAL    (0x07U)
#define CRC8_INITIAL_VALUE (0x00U)

crc8_status_t crc8_calculate(const uint8_t * const data,
                             uint32_t length,
                             uint8_t * const out_crc)
{
    uint8_t crc = CRC8_INITIAL_VALUE;

    if ((NULL == data) || (NULL == out_crc))
    {
        return CRC8_STATUS_INVALID_ARGUMENT;
    }

    for (uint32_t index = 0U; index < length; ++index)
    {
        crc ^= data[index];

        for (uint8_t bit = 0U; bit < 8U; ++bit)
        {
            if (0U != (crc & 0x80U))
            {
                crc = (uint8_t)((crc << 1U) ^ CRC8_POLYNOMIAL);
            }
            else
            {
                crc <<= 1U;
            }
        }
    }

    *out_crc = crc;

    return CRC8_STATUS_SUCCESS;
}
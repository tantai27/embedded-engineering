#include <stddef.h>

#include "crc16.h"

#define CRC16_POLYNOMIAL (0xA001U)
#define CRC16_INITIAL_VALUE (0x0000U)

crc16_status_t crc16_calculate(const uint8_t * const data,
                               uint32_t length,
                               uint16_t * const out_crc)
{
    uint16_t crc = CRC16_INITIAL_VALUE;
    uint32_t index = 0U;
    uint8_t bit = 0U;

    if ((NULL == data) || (NULL == out_crc))
    {
        return CRC16_STATUS_INVALID_ARGUMENT;
    }

    while (index < length)
    {
        crc ^= (uint16_t)data[index];

        for (bit = 0U; bit < 8U; ++bit)
        {
            if (0U != (crc & 1U))
            {
                crc = (crc >> 1U) ^ CRC16_POLYNOMIAL;
            }
            else
            {
                crc >>= 1U;
            }
        }

        ++index;
    }

    *out_crc = crc;

    return CRC16_STATUS_SUCCESS;
}
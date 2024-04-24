#include "STC89C5xRC_RDP.h"
#include "delay.h"

/**
 * @brief  按键扫描
 * @param  无
 * @retval 按键值
 */
unsigned char keyScan(void)
{
    unsigned char keyValue = 0;
    // key1
    if(P31 == 0)
    {
        DelayMs(10);
        while (P31 == 0);
        DelayMs(10);
        keyValue = 1;
    }

    // key2
    if(P30 == 0)
    {
        DelayMs(10);
        while (P30 == 0);
        DelayMs(10);
        keyValue = 2;
    }

    // key3
    if(P32 == 0)
    {
        DelayMs(10);
        while (P32 == 0);
        DelayMs(10);
        keyValue = 3;
    }

    // key4
    if(P33 == 0)
    {
        DelayMs(10);
        while (P33 == 0);
        DelayMs(10);
        keyValue = 4;
    }
    return keyValue;
}
#include "intrins.h"

/**
 * @brief  延时函数
 * @param  ms: 延时时间(毫秒)
 * @retval 无
 */
void DelayMs(unsigned int ms) //@11.0592MHz
{
    unsigned char data i, j;

    while (ms--) {
        _nop_();
        i = 2;
        j = 199;
        do {
            while (--j)
                ;
        } while (--i);
    }
}

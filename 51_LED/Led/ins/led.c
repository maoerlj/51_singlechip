#include "STC89C5xRC_RDP.h"

/**
 * @brief  LED灯初始化
 */
void LED_Info(void)
{
    P2 = 0xFF;
}

/**
 * @brief  LED流水灯状态 0:关闭 1:打开
 */
unsigned int ledFlowingState = 0;

/**
 * @brief  LED流水灯索引
 */
unsigned int ledFlowingIndex = 0;

/**
 * @brief  打开LED流水灯
 */
void openLedFlowing(void)
{
    ledFlowingState = 1;
    ledFlowingIndex = 0;
}

/**
 * @brief  关闭LED流水灯
 */
void closeLedFlowing(void)
{
    ledFlowingState = 0;
    P2              = 0xFF;
}

unsigned getLedFlowingState(void)
{
    return ledFlowingState;
}

/**
 * @brief  LED流水灯
 * @param  无
 * @retval 无
 */
void ledFlowing(void)
{
    if (ledFlowingState == 1) {
        if (ledFlowingIndex >= 8) {
            ledFlowingIndex = 0;
        }
        // 从左到右
        P2 = ~(0x01 << ledFlowingIndex);
        // 从右到左
        // P2 = ~(0x80 >> ledFlowingIndex);
        ledFlowingIndex++;
    }
}
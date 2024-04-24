/**
 * LDE模块 P20-P27
 */
#include "STC89C5xRC_RDP.h"
#include "led.h"
#include "delay.h"

/**
 * LED-分别控制点亮
 */
// void main()
// {
//     // 初始化LED
//     LED_Info();
//     while (1) {
//         // 点亮LED_D1
//         LED_D1 = 0;
//         // 点亮LED_D2
//         LED_D2 = 0;
//         // 点亮LED_D3
//         LED_D3 = 0;
//         // 点亮LED_D4
//         LED_D4 = 0;
//         // 点亮LED_D5
//         LED_D5 = 0;
//         // 点亮LED_D6
//         LED_D6 = 0;
//         // 点亮LED_D7
//         LED_D7 = 0;
//         // 点亮LED_D8
//         LED_D8 = 0;
//     }
// }

/**
 * LED-流水灯
 */
void main()
{
    LED_Info();
    openLedFlowing();
    while (1) {
        DelayMs(500);
        ledFlowing();
    }
}
#include "STC89C5xRC_RDP.H"

/**
 * @brief 定时器0初始化 1毫秒@11.0592MHz
 * @param 无
 * @retval 无
 */
void Timer0_Init(void) // 1毫秒@11.0592MHz
{
    AUXR &= 0x7F; // 定时器时钟12T模式
    TMOD &= 0xF0; // 设置定时器模式
    TMOD |= 0x01; // 设置定时器模式
    TL0 = 0x66;   // 设置定时初始值
    TH0 = 0xFC;   // 设置定时初始值
    TF0 = 0;      // 清除TF0标志
    TR0 = 1;      // 定时器0开始计时
    ET0 = 1;      // 使能定时器0中断
    EA  = 1;      // 打开总中断
    PT0 = 0;      // 定时器0中断优先级最低
}


/**
 * @brief 定时器0中断-模板
 */
// void Timer0_Isr(void) interrupt 1
// {
//     static unsigned int timeCount;
//     TL0 = 0x66; // 设置定时初始值
//     TH0 = 0xFC; // 设置定时初始值
//     timeCount++;
//     if (timeCount >= 1000) {
//         timeCount = 0;
//     }
// }
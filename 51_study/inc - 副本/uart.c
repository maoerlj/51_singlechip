#include "STC89C5xRC_RDP.h"

/**
 * @brief 串口1初始化函数 9600bps@11.0592MHz
 */
void Uart1_Init_9600(void) // 9600bps@11.0592MHz
{
    PCON |= 0x80; // 使能波特率倍速位SMOD
    SCON = 0x50;  // 8位数据,可变波特率
    AUXR &= 0xBF; // 定时器时钟12T模式
    AUXR &= 0xFE; // 串口1选择定时器1为波特率发生器
    TMOD &= 0x0F; // 设置定时器模式
    TMOD |= 0x20; // 设置定时器模式
    TL1 = 0xFA;   // 设置定时初始值
    TH1 = 0xFA;   // 设置定时重载值
    ET1 = 0;      // 禁止定时器中断
    TR1 = 1;      // 定时器1开始计时
    ES  = 1;      // 使能串口中断
    EA  = 1;      // 使能总中断
}

/**
 * @brief 串口1发送一个字节
 * @param dat 要发送的字节
 * @return void
 */
void UART1_SendByte(unsigned char dat)
{
    SBUF = dat;
    // 等待发送完成
    while (!TI)
        ;
    TI = 0;
}

/**
 * @brief 串口1接收
 */
// void Uart1_Isr(void) interrupt 4
// {
// 	if (TI)				//检测串口1发送中断
// 	{
// 		TI = 0;			//清除串口1发送中断请求位
// 	}
// 	if (RI)				//检测串口1接收中断
// 	{
// 		RI = 0;			//清除串口1接收中断请求位
// 	}
// }

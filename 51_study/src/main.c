#include "STC89C5xRC_RDP.H"
#include "intrins.h"
#include "delay.h"
#include "nixie.h"

#include "LCD1602.h"
#include "led.h"
#include "matrixKey.h"
#include "Timer0.h"
#include "key.h"
#include "uart.h"
#include "matrixLED.h"


unsigned char keyNumber;

unsigned int initHour = 24;
unsigned int initMin  = 60;
unsigned int initSec  = 0;
// 小时
unsigned int hour;
// 分钟
unsigned int min;
// 秒数
unsigned int sec;

void main()
{
    // 单个动态数码管轮询显示 注意：注释nixie中消影部分代码
    // unsigned char location = 1, number = 1;
    // while (1) {
    //     nixie(location, showNumber[number],0);
    //     DelayMs(2000);
    //     location++;
    //     number++;
    //     if (location > 8) {
    //         location = 1;
    //     }
    //     if (number > 8) {
    //         number = 1;
    //     }
    // }

    // 多个动态数码管显示 注意：放开nixie中消影部分代码
    // while (1) {
    //     nixie(1, showNumber[1], 1);
    //     nixie(2, showNumber[2], 1);
    // }

    // 矩阵键盘
    // LCD_Init();
    // LCD_ShowString(1, 1, "Hello, World!");
    // while (1) {
    //     unsigned char key = MatrixKey();
    //     if (key != 0) {
    //         LCD_ShowNum(2, 1, key, 2);
    //     }
    // }

    // 矩阵键盘 - 密码锁
    // LCD_Init();
    // LCD_ShowString(1, 1, "Please input:");
    // while (1) {
    //     unsigned char key = MatrixKey();
    //     // 密码区：S1-S10 确认：S11 重置：S12
    //     if (key != 0 && key <= 10) {
    //         key = key % 10;
    //         showColumn++;
    //         if (showColumn <= 6) {
    //             password[showColumn - 1] = key;
    //             LCD_ShowNum(2, showColumn, key, 1);
    //         }
    //     } else if (key == 11) {
    //         // 确认
    //         if (password[0] == 1 && password[1] == 2 && password[2] == 3 && password[3] == 4 && password[4] == 5 && password[5] == 6) {
    //             LCD_ShowString(2, 15, "OK");
    //         } else {
    //             LCD_ShowString(2, 15, "NO");
    //             // 第二行清空
    //             LCD_ShowString(2, 1, "      ");
    //             showColumn  = 0;
    //             password[0] = 0;
    //             password[1] = 0;
    //             password[2] = 0;
    //             password[3] = 0;
    //             password[4] = 0;
    //             password[5] = 0;
    //         }
    //     } else if (key == 12) {
    //         // 重置
    //         LCD_Init();
    //         LCD_ShowString(1, 1, "Please input:");
    //         showColumn  = 0;
    //         password[0] = 0;
    //         password[1] = 0;
    //         password[2] = 0;
    //         password[3] = 0;
    //         password[4] = 0;
    //         password[5] = 0;
    //     }
    // }

    // 定时器：1）用于计时系统 2）替代长时间的Delay，提高cpu的运行效率

    // 定时器0中断-LDE闪烁
    // Timer0_Init();
    // while (1) {
    //     keyNumber = keyScan();
    //     if (keyNumber == 1) {
    //         if (getLedFlowingState() == 1) {
    //             closeLedFlowing();
    //         } else {
    //             openLedFlowing();
    //         }
    //     }
    // }

    // 定时器倒计时
    // hour = initHour;
    // min  = initMin;
    // sec  = initSec;
    // LCD_Init();
    // LCD_ShowString(1, 1, "Countdown:");
    // Timer0_Init();
    // while (1) {
    //     LCD_ShowNum(2, 1, hour, 2);
    //     LCD_ShowString(2, 3, ":");
    //     LCD_ShowNum(2, 4, min, 2);
    //     LCD_ShowString(2, 6, ":");
    //     LCD_ShowNum(2, 7, sec, 2);
    // }

    /** 串口通信
     * 串口通信是一种通过串行通信接口进行数据传输的通信方式，它是一种全双工通信方式，即可以同时进行发送和接收操作。
     * TTL电平 0V-0 5V-1 （距离短<10多米>，速度快）
     * RS232电平 -3~-15V-0 +3~+15V-1 （距离长<1200米>，速度慢）（用于高电压之间的通信）
     * RS485电平 两线压差 +2~+6V-1 -2~-6V-0 (差分信号) （距离长<1200米>，速度慢）
     *
     * TXD - 发送端
     * RXD - 接收端
     * RST - 复位
     * VCC - 电源
     * GND - 地
     * IO  - 串口通信
     * CTS - 清除发送
     * RTS - 请求发送
     * DSR - 数据就绪
     * DTR - 数据终端就绪
     * DCD - 数据载波检测
     * SG  - 信号地
     * RI  - 振铃指示
     * EN  - 使能
     * 3V3 - 3.3V电源
     * 串口通信的波特率：9600 19200 38400 57600 115200
     *
     * 全双工：通信双方可以在同一时刻互相传输数据
     * 半双工：通信双方可以互相传 输数据，但不能同时传输，必须分时复用一根数据线
     * 单工：通信只能有一方发送到另一方，不能反向传输
     *
     * 异步：通信双方各自约定通信速率
     * 同步：通信双方靠一根时钟线来约定通信速率
     *
     * 总线：连接各个设备的数据传输线路（类似于一条马路，把路边各住户连接起来，使住户可以相互交流）
     *
     * 串行口相关寄存器：
     * SCON - 串口控制寄存器
     * SBUF - 串口数据寄存器
     * PCON - 电源控制寄存器
     * IE   - 中断控制寄存器
     * IPH  - 中断优先级高位寄存器
     * IP   - 中断优先级寄存器
     * SADEN - 从机地址寄存器
     * SADDR - 从机地址寄存器
     */
    // Uart1_Init_9600();
    // while (1) {
    // }

    /**
     * LED点阵屏 8*8 单色
     */
    // _74HC595_Wr iteByte(0xFF); // 0xAA 10101010
    // P0 = 0x7F;                // 01111111
    MatrixLED_Init();
    while (1) {
        /* code */
        // MatrixLED_ShowColumn(0, 0x30, 1); // 00110000
        // MatrixLED_ShowColumn(1, 0x78, 1); // 01111000
        // MatrixLED_ShowColumn(2, 0x3C, 1); // 00111100
        // MatrixLED_ShowColumn(3, 0x1E, 1); // 00011110
        // MatrixLED_ShowColumn(4, 0x3C, 1); // 00111100
        // MatrixLED_ShowColumn(5, 0x78, 1); // 01111000
        // MatrixLED_ShowColumn(6, 0x30, 1); // 00110000
        MatrixLED_ShowScroll(Hello, sizeof(Hello) / sizeof(Hello[0]));
    }

    /**
     * DS1302时钟模块
     */
}

/**
 * @brief 定时器0中断-LDE闪烁
 */
// void Timer0_Isr(void) interrupt 1
// {
//     static unsigned int timeCount;
//     TL0 = 0x66; // 设置定时初始值
//     TH0 = 0xFC; // 设置定时初始值
//     timeCount++;
//     if (timeCount >= 1000) {
//         timeCount = 0;
//         ledFlowing();
//     }
// }

/**
 * 定时器倒计时
 */
// void Timer0_Isr(void) interrupt 1
// {
//     static unsigned int timeCount;
//     TL0 = 0x66; // 设置定时初始值
//     TH0 = 0xFC; // 设置定时初始值
//     timeCount++;
//     if (timeCount >= 1000) {
//         timeCount = 0;

//         if (sec == 0 && (min != 0 || hour != 0)) {
//             min--;
//             sec = 60;
//         }
//         if (min == 0 && hour != 0) {
//             hour--;
//             min = initMin;
//         }
//         if (min != 0 || hour != 0 || sec != 0) {
//             sec--;
//         }
//     }
// }

/**
 * 定时器0中断-串口通信
 */
// void Timer0_Isr(void) interrupt 1
// {
//     static unsigned int timeCount;
//     TL0 = 0x66; // 设置定时初始值
//     TH0 = 0xFC; // 设置定时初始值
//     timeCount++;
//     if (timeCount >= 1000) {
//         timeCount = 0;
//         UART1_SendByte(0x55);
//     }
// }

/**
 * @brief 串口1接收
 */
// void Uart1_Isr(void) interrupt 4
// {
//     if (TI) // 检测串口1发送中断
//     {
//         TI = 0; // 清除串口1发送中断请求位
//     }
//     if (RI) // 检测串口1接收中断
//     {
//         RI = 0; // 清除串口1接收中断请求位
//         P2 = SBUF;
//         UART1_SendByte(SBUF);
//     }
// }
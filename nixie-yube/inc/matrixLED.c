#include "STC89C5xRC_RDP.h"
#include "intrins.h"
#include "delay.h"

sbit RCK = P3 ^ 5;
sbit SCK = P3 ^ 6;
sbit SER = P3 ^ 4;

/**
 * @brief 矩阵LED初始化
 */
void MatrixLED_Init(void)
{
    SCK = 0;
    RCK = 0;
}

/**
 * @brief 74HC595写入一个字节
 * @param Byte 要写入的字节
 */
void _74HC595_WriteByte(unsigned char Byte)
{
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SER = Byte >> 7;
        Byte <<= 1;
        SCK = 0;
        _nop_();
        _nop_();
        SCK = 1;
    }
    RCK = 0;
    _nop_();
    _nop_();
    RCK = 1;
}

/**
 * @brief 显示一个列
 * @param column 列号 0-7
 * @param byt 要显示的字节 1-亮 0-灭 (16进制)
 * @param isClear 是否消影 1-是 0-否
 */
void MatrixLED_ShowColumn(unsigned char column, unsigned char byt, unsigned char isClear)
{
    _74HC595_WriteByte(byt);
    P0 = ~(0x80 >> column);
    // 消影
    if (isClear) {
        DelayMs(1);
        P0 = 0xFF;
    }
}

unsigned i, offset = 0, count = 0;

void MatrixLED_ShowScroll(unsigned char *showStr, unsigned int len)
{
    for (i = 0; i < 8; i++) {
        MatrixLED_ShowColumn(i, showStr[i + offset], 1);
    }
    count++;
    if (count > 20) {
        count = 0;
        offset++;
    }
    if (offset > (len - 8)) {
        offset = 0;
    }
}

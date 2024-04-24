#include "REG51.H"
#include "delay.h"

// 段码
sbit P0_0 = P0 ^ 0;
sbit P0_1 = P0 ^ 1;
sbit P0_2 = P0 ^ 2;
sbit P0_3 = P0 ^ 3;
sbit P0_4 = P0 ^ 4;
sbit P0_5 = P0 ^ 5;
sbit P0_6 = P0 ^ 6;
sbit P0_7 = P0 ^ 7;

// 位码
sbit P2_2 = P2 ^ 2;
sbit P2_3 = P2 ^ 3;
sbit P2_4 = P2 ^ 4;

/**
 * @brief  数码管显示
 * @param  location: 位码
 * @param  number: 段码 （0-9,A-F）showNumber[]
 * @param  isClear: 是否消影 1消影 0不消影
 * @retval 无
 */
void nixie(unsigned char location, number, unsigned int isClear)
{
    switch (location) {
        case 1:
            P2_4 = 1;
            P2_3 = 1;
            P2_2 = 1;
            break;
        case 2:
            P2_4 = 1;
            P2_3 = 1;
            P2_2 = 0;
            break;
        case 3:
            P2_4 = 1;
            P2_3 = 0;
            P2_2 = 1;
            break;
        case 4:
            P2_4 = 1;
            P2_3 = 0;
            P2_2 = 0;
            break;
        case 5:
            P2_4 = 0;
            P2_3 = 1;
            P2_2 = 1;
            break;
        case 6:
            P2_4 = 0;
            P2_3 = 1;
            P2_2 = 0;
            break;
        case 7:
            P2_4 = 0;
            P2_3 = 0;
            P2_2 = 1;
            break;
        case 8:
            P2_4 = 0;
            P2_3 = 0;
            P2_2 = 0;
            break;
        default:
            break;
    }
    P0 = number;

    // 消影
    if (isClear == 1) {
        DelayMs(1);
        P0 = 0x00;
    }
}

/**
 * @brief  数码管显示码表
 */
int showNumber[] = {
    0x3f, // 0  0x3f->0011 1111
    0x06, // 1  0x06->0000 0110
    0x5b, // 2  0x5b->0101 1011
    0x4f, // 3  0x4f->0100 1111
    0x66, // 4  0x66->0110 0110
    0x6d, // 5  0x6d->0110 1101
    0x7d, // 6  0x7d->0111 1101
    0x07, // 7  0x07->0000 0111
    0x7f, // 8  0x7f->0111 1111
    0x6f, // 9  0x6f->0110 1111
    0x77, // A  0x77->0111 0111
    0x7c, // b  0x7c->0111 1100
    0x39, // C  0x39->0011 1001
    0x5e, // d  0x5e->0101 1110
    0x79, // E  0x79->0111 1001
    0x71, // F  0x71->0111 0001
    0x00, // 空 0x00->0000 0000
};

void nixieShowNumber(int number)
{
    nixie(1, showNumber[number / 1000], 1);
    nixie(2, showNumber[number % 1000 / 100], 1);
    nixie(3, showNumber[number % 100 / 10], 1);
    nixie(4, showNumber[number % 10], 1);
}
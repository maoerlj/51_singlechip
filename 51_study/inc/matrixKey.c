#include "REG51.H"
#include "delay.h"

// 行
sbit Row1 = P1 ^ 7;
sbit Row2 = P1 ^ 6;
sbit Row3 = P1 ^ 5;
sbit Row4 = P1 ^ 4;

// 列
sbit Col1 = P1 ^ 3;
sbit Col2 = P1 ^ 2;
sbit Col3 = P1 ^ 1;
sbit Col4 = P1 ^ 0;

/**
 * @brief  矩阵键盘扫描
 *         按列扫描，按行扫描可能会影响蜂鸣器的使用
 * @param  无
 * @retval 按键值 
 */
unsigned char MatrixKey()
{ 
    unsigned char key = 0;

    P1   = 0xff;
    Col1 = 0;
    if (Row1 == 0) {DelayMs(10);while (Row1 == 0);DelayMs(10);key = 1;}
    if (Row2 == 0) {DelayMs(10);while (Row2 == 0);DelayMs(10);key = 5;}
    if (Row3 == 0) {DelayMs(10);while (Row3 == 0);DelayMs(10);key = 9;}
    if (Row4 == 0) {DelayMs(10);while (Row4 == 0);DelayMs(10);key = 13;}

    P1   = 0xff;
    Col2 = 0;
    if (Row1 == 0) {DelayMs(10);while (Row1 == 0);DelayMs(10);key = 2;}
    if (Row2 == 0) {DelayMs(10);while (Row2 == 0);DelayMs(10);key = 6;}
    if (Row3 == 0) {DelayMs(10);while (Row3 == 0);DelayMs(10);key = 10;}
    if (Row4 == 0) {DelayMs(10);while (Row4 == 0);DelayMs(10);key = 14;}

    P1   = 0xff;
    Col3 = 0;
    if (Row1 == 0) {DelayMs(10);while (Row1 == 0);DelayMs(10);key = 3;}
    if (Row2 == 0) {DelayMs(10);while (Row2 == 0);DelayMs(10);key = 7;}
    if (Row3 == 0) {DelayMs(10);while (Row3 == 0);DelayMs(10);key = 11;}
    if (Row4 == 0) {DelayMs(10);while (Row4 == 0);DelayMs(10);key = 15;}

    P1   = 0xff;
    Col4 = 0;
    if (Row1 == 0) {DelayMs(10);while (Row1 == 0);DelayMs(10);key = 4;}
    if (Row2 == 0) {DelayMs(10);while (Row2 == 0);DelayMs(10);key = 8;}
    if (Row3 == 0) {DelayMs(10);while (Row3 == 0);DelayMs(10);key = 12;}
    if (Row4 == 0) {DelayMs(10);while (Row4 == 0);DelayMs(10);key = 16;}

    return key;
}
#ifndef __MATRIXKEY_H
#define __MATRIXKEY_H

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

unsigned char showColumn = 0, password[6] = {0, 0, 0, 0, 0, 0};

unsigned char MatrixKey();

#endif
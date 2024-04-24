/**
 * DS1302 时钟模块
 */
#include "STC89C5xRC_RDP.h"

// DS1302 时钟模块的引脚定义
sbit DS1302_SCLK = P3 ^ 6;
sbit DS1302_CE   = P3 ^ 5;
sbit DS1302_IO   = P3 ^ 4;

// 寄存器写入地址/指令定义
#define DS1302_SECOND 0x80 // 秒
#define DS1302_MINUTE 0x82 // 分
#define DS1302_HOUR   0x84 // 时
#define DS1302_DAY    0x8A // 星期
#define DS1302_DATE   0x86 // 日
#define DS1302_MONTH  0x88 // 月
#define DS1302_YEAR   0x8C // 年
#define DS1302_WP     0x8E // 写保护

void DS1302_WriteByte(unsigned char command, unsigned char dat);

/**
 * @brief DS1302 时钟模块初始化
 */
void DS1302_Init(void)
{
    DS1302_CE   = 0;
    DS1302_SCLK = 0;

    // DS1302_WriteByte(0x8E, 0x00); // 关闭写保护
}

/**
 * @brief DS1302 时钟模块写入字节
 * @param command 写入命令 0x80:秒 0x82:分 0x84:时 0x86:日 0x88:月 0x8A:星期 0x8C:年
 * @param dat 写入数据 (10进制)
 */
void DS1302_WriteByte(unsigned char command, unsigned char dat)
{
    // 十进制数转换为BCD码：BCD=DEC/10*16+DEC%10 （2位BCD码）
    unsigned char i;
    DS1302_CE = 1;
    for (i = 0; i < 8; i++) {
        DS1302_IO   = command & (0x01 << i); // &0x01 取最低位
        DS1302_SCLK = 1;
        // 由于单片机操作速度没有DS1302快，所以不需要延时。单片机运行周期是1微秒，DS1302的时钟运行速率是纳秒级别。
        DS1302_SCLK = 0;
    }

    for (i = 0; i < 8; i++) {
        DS1302_IO   = dat & (0x01 << i); // &0x01 取最低位
        DS1302_SCLK = 1;
        // 由于单片机操作速度没有DS1302快，所以不需要延时。单片机运行周期是1微秒，DS1302的时钟运行速率是纳秒级别。
        DS1302_SCLK = 0;
    }

    DS1302_CE = 0;
}

/**
 * @brief DS1302 时钟模块读取字节
 * @param command 读取命令 0x81:秒 0x83:分 0x85:时 0x87:日 0x89:月 0x8B:星期 0x8D:年
 * @return 读取数据 (10进制)
 */
unsigned char DS1302_ReadByte(unsigned char command)
{
    unsigned char i, dat = 0x00;
    command |= 0x01; // 将指令转换为读指令
    DS1302_CE = 1;
    for (i = 0; i < 8; i++) {
        DS1302_IO   = command & (0x01 << i); // &0x01 取最低位
        DS1302_SCLK = 0;
        DS1302_SCLK = 1;
    }
    for (i = 0; i < 8; i++) {
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
        if (DS1302_IO) {
            dat |= (0x01 << i);
        }
    }
    DS1302_CE = 0;
    DS1302_IO = 0;

    // BCD码: 用4位二进制数表示一个十进制数的一位，称为BCD码
    // 例如：0001 0011 表示13, 1000 0101 表示85, 0001 1010 不合法
    // BCD码转换为十进制数：DEC=BCD/16*10+BCD%16 （2位BCD码）
    // 十进制数转换为BCD码：BCD=DEC/10*16+DEC%10 （2位BCD码）
    dat = (dat / 16 * 10) + (dat % 16);
    return dat;
}

void DS1302_WriteTime(unsigned char year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second)
{
    DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
    DS1302_WriteByte(DS1302_YEAR, year / 10 * 16 + year % 10);
    DS1302_WriteByte(DS1302_MONTH, month / 10 * 16 + month % 10);
    DS1302_WriteByte(DS1302_DATE, day / 10 * 16 + day % 10);
    DS1302_WriteByte(DS1302_HOUR, hour / 10 * 16 + hour % 10);
    DS1302_WriteByte(DS1302_MINUTE, minute / 10 * 16 + minute % 10);
    DS1302_WriteByte(DS1302_SECOND, second / 10 * 16 + second % 10);
    DS1302_WriteByte(DS1302_WP, 0x00); // 开启写保护
}

/**
 * @brief DS1302 时钟模块写入年
 */
void DS1302_WriteYear(unsigned char year)
{
    DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
    DS1302_WriteByte(DS1302_YEAR, year / 10 * 16 + year % 10);
    DS1302_WriteByte(DS1302_WP, 0x00); // 开启写保护
}

/**
 * @brief DS1302 时钟模块写入月
 */
void DS1302_WriteMonth(unsigned char month)
{
    DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
    DS1302_WriteByte(DS1302_MONTH, month / 10 * 16 + month % 10);
    DS1302_WriteByte(DS1302_WP, 0x00); // 开启写保护
}

/**
 * @brief DS1302 时钟模块写入日
 */
void DS1302_WriteDay(unsigned char day)
{
    DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
    DS1302_WriteByte(DS1302_DATE, day / 10 * 16 + day % 10);
    DS1302_WriteByte(DS1302_WP, 0x00); // 开启写保护
}

/**
 * @brief DS1302 时钟模块写入时
 */
void DS1302_WriteHour(unsigned char hour)
{
    DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
    DS1302_WriteByte(DS1302_HOUR, hour / 10 * 16 + hour % 10);
    DS1302_WriteByte(DS1302_WP, 0x00); // 开启写保护
}

/**
 * @brief DS1302 时钟模块写入分
 */
void DS1302_WriteMinute(unsigned char minute)
{
    DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
    DS1302_WriteByte(DS1302_MINUTE, minute / 10 * 16 + minute % 10);
    DS1302_WriteByte(DS1302_WP, 0x00); // 开启写保护
}

/**
 * @brief DS1302 时钟模块写入秒
 */
void DS1302_WriteSecond(unsigned char second)
{
    DS1302_WriteByte(DS1302_WP, 0x00); // 关闭写保护
    DS1302_WriteByte(DS1302_SECOND, second / 10 * 16 + second % 10);
    DS1302_WriteByte(DS1302_WP, 0x00); // 开启写保护
}

/**
 * @brief DS1302 时钟模块读取年
 */
unsigned char DS1302_ReadYear(void)
{
    return DS1302_ReadByte(DS1302_YEAR);
}

/**
 * @brief DS1302 时钟模块读取月
 */
unsigned char DS1302_ReadMonth(void)
{
    return DS1302_ReadByte(DS1302_MONTH);
}

/**
 * @brief DS1302 时钟模块读取日
 */
unsigned char DS1302_ReadDay(void)
{
    return DS1302_ReadByte(DS1302_DATE);
}

/**
 * @brief DS1302 时钟模块读取时
 */
unsigned char DS1302_ReadHour(void)
{
    return DS1302_ReadByte(DS1302_HOUR);
}

/**
 * @brief DS1302 时钟模块读取分
 */
unsigned char DS1302_ReadMinute(void)
{
    return DS1302_ReadByte(DS1302_MINUTE);
}

/**
 * @brief DS1302 时钟模块读取秒
 */
unsigned char DS1302_ReadSecond(void)
{
    return DS1302_ReadByte(DS1302_SECOND);
}

/**
 * @brief DS1302 时钟模块读取星期
 */
unsigned char DS1302_ReadWeek(void)
{
    return DS1302_ReadByte(DS1302_DAY);
}
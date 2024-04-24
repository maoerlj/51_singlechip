#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_Init(void);
void DS1302_WriteByte(unsigned char command, unsigned char dat);
unsigned char DS1302_ReadByte(unsigned char command);

void DS1302_WriteTime(unsigned char year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second);

void DS1302_WriteYear(unsigned char year);
void DS1302_WriteMonth(unsigned char month);
void DS1302_WriteDay(unsigned char day);
void DS1302_WriteHour(unsigned char hour);
void DS1302_WriteMinute(unsigned char minute);
void DS1302_WriteSecond(unsigned char second);

unsigned char DS1302_ReadYear(void);
unsigned char DS1302_ReadMonth(void);
unsigned char DS1302_ReadDay(void);
unsigned char DS1302_ReadHour(void);
unsigned char DS1302_ReadMinute(void);
unsigned char DS1302_ReadSecond(void);
unsigned char DS1302_ReadWeek(void);


#endif
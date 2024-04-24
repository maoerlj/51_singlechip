#ifndef __LED_H__
#define __LED_H__

#include "STC89C5xRC_RDP.h"

#define LED_D1 P20
#define LED_D2 P21
#define LED_D3 P22
#define LED_D4 P23
#define LED_D5 P24
#define LED_D6 P25
#define LED_D7 P26
#define LED_D8 P27

void LED_Info(void);
void openLedFlowing(void);
void closeLedFlowing(void);
unsigned getLedFlowingState(void);
void ledFlowing(void);
#endif
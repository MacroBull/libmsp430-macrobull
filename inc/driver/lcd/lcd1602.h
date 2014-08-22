

#ifndef __LCD1602_H
#define __LCD1602_H

#include <msp430.h>
#include <stdint.h>


#include "hal/perip.h"
// #include "bsp/exp430f5529lp.h"

#include "pwm/pwm.h"


// #include "ADS1x9x_main.h"

#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)
// #define ABS(a) (a>0?a:-a)
//#define CPU_FREQ 1100000
#define DELAY_1US (CPU_FREQ / 100000)
//#define DELAY_1US (CPU_FREQ / 1000000)

extern void initial_lcd(void);
extern void LCD_setContrast(uint16_t BL, uint16_t CON, uint16_t M);
extern void LCD_Disp(char x,char y,char *character);
extern void LCD_Trans(char in[]);


#endif

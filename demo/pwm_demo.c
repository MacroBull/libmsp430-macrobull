/*
 * @author : macrobull
 * for msp430f5529 with 4 TA outputs
 * for msp430g2553 with 1 TA output
 */

#include <msp430.h>

#include "dev.h"
#include "pwm.h"

#define M 2000

int main(void)
{
	WDT_disable;
	TA_PWM_enable(_TA_PWM0, SMCLK, UP, BIT0 + BIT1 + BIT2 + BIT3, M); // enable 4 TA out, up mode
	TA_PWM_enable(_TA_PWM1, SMCLK, UP_DOWN, BIT0+BIT1, M); // enable 2 TA out, up_down mode
	
	P1DIR |= BIT0; // Loop indicator
	int i = 0;
	while (1){
		i++;
		
		TA_PWM_setter( _TA_PWM0, 1, i, POUT); // +duty%
		TA_PWM_setter( _TA_PWM0, 2, i & 0x7f, POUT);
		TA_PWM_setter( _TA_PWM0, 3, i ^ 0x233, POUT);
		TA_PWM_setter( _TA_PWM0, 4, i, NOUT); // -duty%
		TA_PWM_setter( _TA_PWM1, 1, i, POUT);
		TA_PWM_setter( _TA_PWM1, 2, i, NOUT);
	
		if (i> M) {
			i = 0;
		P1OUT ^= BIT0;
		}
		__delay_cycles(1000);
	}

	_BIS_SR(CPUOFF);
}

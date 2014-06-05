/*
 * @author : macrobull
 * for msp430f5529 with 4 TA outputs
 * for msp430g2553 with 1 TA output
 */

#include <msp430.h>

#include "wdt.h"
#include "hal/perip.h"
#include "bsp/exp430g2.h"

#include "pwm/pwm.h"

#define M 2000

int main(void)
{
	WDT_DISABLE;

	pwm_enable(PWM0, PWMSRC_SMCLK, PWM_UP, BIT1,  M); // enable 4 TA0 out, up mode
 	pwm_enable(PWM1, PWMSRC_SMCLK, PWM_UP_DOWN, BIT1 + BIT2, M); // enable 2 TA1 out, u_down mode
// 	pwm_enable(PWM2, PWMSRC_SMCLK, PWM_UP, BIT1 + BIT2, M); // enable 2 TA 2out, continuous mode

	P1DIR |= BIT0; // Loop indicator
	
	P2DIR = ~0;
	P2SEL = ~0;
	
	int i = 0;
	while (1){
		if (i++> M) {
			i = 1;
			P1OUT ^= BIT0;
		}

		pwm_set( PWM0, 1, i, PWM_POUT); // +duty%
		pwm_set( PWM1, 1, i, PWM_POUT);
		pwm_set( PWM1, 2, i, PWM_NOUT);
// 		pwm_set( PWM2, 1, i, PWM_POUT);
// 		pwm_set( PWM2, 2, i, PWM_NOUT);

		__delay_cycles(1000);
	}

//	_BIS_SR(CPUOFF);
}

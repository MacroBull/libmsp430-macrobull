/*
 * @author : macrobull
 * for msp430f5529 with 4 TA outputs
 * for msp430g2553 with 1 TA output
 */

#include <msp430.h>

#include "wdt.h"
#include "hal/perip/f5529.h"
#include "bsp/exp430f5529lp.h"

#include "pwm/pwm.h"

#define M 2000

int main(void)
{
	WDT_DISABLE;

	pwm_enable(PWM0, PWMSRC_SMCLK, PWM_UP, BIT1 + BIT2 + BIT3 + BIT4, M); // enable 4 TA0 out, up mode
	pwm_enable(PWM1, PWMSRC_SMCLK, PWM_UP_DOWN, BIT1 + BIT2, M); // enable 2 TA1 out, u_down mode
	pwm_enable(PWM2, PWMSRC_SMCLK, PWM_UP, BIT1 + BIT2, M); // enable 2 TA 2out, continuous mode

	P2DIR = ~0;
	P2SEL= ~0;

	P1DIR |= BIT0; // Loop indicator
	int i = 0;
	while (1){
		if (i++> M) {
			i = 1;
			P1OUT ^= BIT0;
		}

		pwm_setter( PWM0, 1, i, PWM_POUT); // +duty%
		pwm_setter( PWM0, 2, i & 0x7f, PWM_POUT);
		pwm_setter( PWM0, 3, i ^ 0x233, PWM_POUT);
		pwm_setter( PWM0, 4, i, PWM_NOUT); // -duty%
		pwm_setter( PWM1, 1, i, PWM_POUT);
		pwm_setter( PWM1, 2, i, PWM_NOUT);
		pwm_setter( PWM2, 1, i, PWM_POUT);
		pwm_setter( PWM2, 2, i, PWM_NOUT);

		__delay_cycles(1000);
	}

//	_BIS_SR(CPUOFF);
}

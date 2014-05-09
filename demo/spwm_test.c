#include <msp430.h>


#include "wdt.h"
#include "calib_val.h"
//#include "spwm_table_65536_1024.h"

#include "pwm/pwm.h"

#include "pwm/spwm/spwm_table_65536_1024.h"

#include "def/perip/g2452.h"
#include "def/pin/exp430g2.h"

void main(){
	WDT_DISABLE;
	BC16MSET;
	
	PWM_enable(PWM0, SMCLK, UP, BIT0, 0xff);
	
	P1DIR = 0xff;
	P1SEL = 0xff;
	
	unsigned int i;
	while (1){
		i++;
		PWM_setter(PWM0, 1, 100 + (SPWM_DATA[(i << 2) & 1023]>>9), POUT);
		//PWM_setter(PWM0, 1, 0x80, POUT);
	}
	
	
	_BIS_SR(CPUOFF);
}


#include <msp430.h>
#include <stdint.h>

#include "calib_val.h"
#include "wdt.h"

uint16_t cnt;

#define LED0 BIT0

#define S_OUT BIT3

#define B0 BIT2
#define B1 BIT4

#define DELTA 150

uint16_t baseline;

void cap_init(){
	
	P1DIR &= ~B0;
	
	P1SEL |= B0;
// 	P1SEL2 |= B0;
	CCTL1 = CM_3 + CCIS_0 + CAP + CCIE;
	
	P1DIR &= ~B1;
	
	P1SEL |= B1;
	P1SEL2 |= B1;
// 	CCTL2 = CM_3 + CCIS_0 + CAP + CCIE;
	
// 	P1IES |= B0;
	
// 	P1DIR |= S_OUT;
	P1DIR &= ~S_OUT;
	P1REN |= S_OUT;
	
}

int main(void)
{
	BC16MSET;
	WDT_DISABLE;
	
	cap_init();
	display_init();
	
	P1DIR |= LED0;
	P1OUT &= ~LED0;
	
	_BIS_SR(CPUOFF);
	
}

// Timer_A3 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
	switch( TAIV )
	{
		case  2: 
			cnt = CCR1 - cnt;
			break;
		case 4:
 			cnt = CCR2 - cnt;
 			break;
		case	10:
			display(cnt);
			
			if (cnt > baseline+ DELTA)
				P1OUT ^= LED0;
			
			baseline = (baseline + cnt) >> 1;
			
			
			P1OUT ^= S_OUT;
			cnt = TAR;
// 			P1IE |= B0;
			break;
	}
}

// // Port 1 interrupt service routine
// #pragma vector=PORT1_VECTOR
// __interrupt void Port_1(void)
// {
// 	cnt = TAR;
// 	P1OUT ^= LED0;                            // P1.0 = toggle
// 	P1IFG &= ~B0;                           // P1.4 IFG cleared
// 	P1IE &= ~B0;
// }



/*
 * 
 *
 */


#include <msp430.h>
#include "wdt.h"
#include "hal/perip/f5529.h"
#include "bsp/exp430f5529lp.h"

#include "timer.h"
#include "isr_wrapper.h"


void f0(uint16_t count){ // flash green LED for event 
	P4OUT ^= BIT7;
}

void f1(uint16_t count){ // flash red LED for event 
	P1OUT ^= BIT0;
}

int16_t f2(uint16_t vector, int16_t count){ // flash green LED for raw callback
	P4OUT ^= BIT7;
	return 0;
}

int16_t f3(uint16_t vector, int16_t count){ // flash red LED for raw callback
	P1OUT ^= BIT0;
	return 0;
}


_ISR_callback_16 callback_list[] = {f2, f3, NULL}; // raw callback list, assure it end with NULL

event_obj event_list[] = {
	{
		.enable = 1,
		.period = 3,
		.callback = f0
	},
	{
		.enable = 1,
		.period = 7,
		.callback = f1
	}
}; // events list, two flash events in different periods

char mode = 0;

void main(){
	
	WDT_DISABLE;

	P1DIR |= BIT0; //enable LED
	P4DIR |= BIT7;
	
	P1DIR &= ~BIT1;
	P1REN |= BIT1;
	P1OUT |= BIT1; //pull up for pushButton
	P1IES |= BIT1;
	P1IE |= BIT1;  //enable pushButton Interrupt
	
	timer_env_set(TIMER_CNT, TIMER_TABLE); // set timer_event environment
	timer_init(TIMER2, TSRC_SMCLK, 40000); // set timer2(Timer_A2) in period of 4000 SMCLKs
	
	while (1){
		
		if (mode){
			timer_event_set(TIMER2, 2,  event_list); //makes timer2 in event mode
		}
		else {
// 			timer_event_reset(TIMER2);  // no need for direct change in below
			TIMER2_A1_ISR_callbacks = callback_list;  // overide callbacks to change mode XD
			timer_interrupt_enable(TIMER2);
			
		}
		
		_BIS_SR(CPUOFF+GIE);
	}
}

#pragma vector=PORT1_VECTOR
__interrupt void buttonPushed(){
	
	mode ^= 1; // change the mode
	P1IFG &= ~BIT1;
	_BIC_SR_IRQ(CPUOFF); // dispatch the change
}


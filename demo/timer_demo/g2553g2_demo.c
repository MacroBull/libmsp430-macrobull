
#include <msp430.h>
#include "wdt.h"
#include "calib_val.h"
#include "hal/perip.h"
#include "bsp/exp430g2.h"

#include "timer.h"
#include "isr_wrapper.h"


void f0(uint16_t count){ // flash green LED for event 
	P1OUT ^= BIT6;
}

void f1(uint16_t count){ // flash red LED for event 
	P1OUT ^= BIT0;
}

int16_t f2(uint16_t vector, int16_t count){ // flash red LED for raw callback
	P1OUT ^= BIT0;
	return 0;
}


isr_callback_16 callback_list[] = {f2, NULL}; // raw callback list, assure it end with NULL

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

	P1DIR |= BIT0 + BIT6;
	
	P1DIR &= ~BIT3;
	P1REN |= BIT3;
	P1OUT |= BIT3; //pull up for pushButton
	P1IES |= BIT3;
	P1IE |= BIT3;  //enable pushButton Interrupt
	
	timer_env_set(TIMER_CNT, TIMER_TABLE); // set timer_event environment
	timer_init(TIMER1, TSRC_SMCLK, 40000); // set timer2(Timer_A2) in period of 4000 SMCLKs
	
	while (1){
		
		if (mode){
			TIMER1_A1_ISR_callbacks = timer_event_set(TIMER1, 2,  event_list); //makes timer2 in event mode
		}
		else {
// 			timer_event_reset(TIMER1);  // no need for direct change in below
			TIMER1_A1_ISR_callbacks = callback_list;  // overide callbacks to change mode XD
			timer_interrupt_enable(TIMER1);
			
		}
		
		_BIS_SR(CPUOFF+GIE);
	}
}

#pragma vector=PORT1_VECTOR
__interrupt void buttonPushed(){
	
	mode ^= 1; // change the mode
	P1IFG &= ~BIT3;
	_BIC_SR_IRQ(CPUOFF); // dispatch the change
}






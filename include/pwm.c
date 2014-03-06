

#include <msp430.h>

#include "pwm.h"


void TA_PWM_enable(TA_PWM_info *this, uint16_t clock_source, char counter_mode, uint8_t outputs, uint16_t period){
	
	*this->CTL &= ~STOP;
	
	*this->PORT_DIR &= ~(this->TAs << this->TA1 );
	*this->PORT_SEL &= ~(this->TAs << this->TA1 );
	
	*this->PORT_DIR |= outputs << this->TA1;
	*this->PORT_SEL |= outputs << this->TA1;
	
	this->TAs = outputs;
	
	
	if (UP_DOWN == counter_mode)
		*this->_CCR0 = period >> 1; 
	if (UP == counter_mode)
		*this->_CCR0 = period - 1; 
	
	*this->CTL  = clock_source + counter_mode; // + TACLR; 
  
}

void TA_PWM_setter(TA_PWM_info *this, uint8_t cc_id, uint16_t cc_cnt, uint16_t cc_mode){
	
	*this->CCR[cc_id] = cc_cnt; 
	*this->CCTL[cc_id] = cc_mode; 
	
}


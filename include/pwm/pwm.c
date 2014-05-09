

#include <msp430.h>

#include "pwm/pwm.h"


void PWM_enable(PWM_HANDLE this, uint16_t clock_source, char counter_mode, uint8_t outputs, uint16_t period){
	
	*this->CTL &= ~STOP;
	
	*this->PORT_DIR &= ~(this->OUTs << this->OUT0 );
	*this->PORT_SEL &= ~(this->OUTs << this->OUT0 );
	//*this->PORT_SEL2 |= this->OUTs << this->OUT0;
	
	
	*this->PORT_DIR |= outputs << this->OUT0;
	*this->PORT_SEL |= outputs << this->OUT0;
	*this->PORT_SEL2 &= ~(outputs << this->OUT0 );
	
	this->OUTs = outputs;
	
	
	if (UP_DOWN == counter_mode)
		*this->_CCR0 = period >> 1; 
	if (UP == counter_mode)
		*this->_CCR0 = period - 1; 
	
	*this->CTL  = clock_source + counter_mode; // + TACLR; 
  
}

void PWM_setter(PWM_HANDLE this, uint8_t cc_id, uint16_t cc_cnt, uint16_t cc_mode){
	
	*this->CCR[cc_id] = cc_cnt; 
	*this->CCTL[cc_id] = cc_mode; 
	
}


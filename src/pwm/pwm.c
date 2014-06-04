

#include <msp430.h>

#include "pwm/pwm.h"
#include "pwm/pwm_obj.h"

inline void pwm_port_enable(pwm_handle this, uint8_t outputs){
	*this->PORT_DIR &= ~(this->OUTs << this->OUT1 );
	*this->PORT_SEL &= ~(this->OUTs << this->OUT1 );
	//*this->PORT_SEL2 |= this->OUTs << this->OUT1;
	
	*this->PORT_DIR |= outputs << this->OUT1;
	*this->PORT_SEL |= outputs << this->OUT1;
	*this->PORT_SEL2 &= ~(outputs << this->OUT1 );
}

void pwm_enable(pwm_handle this, uint16_t clock_source, char counter_mode, uint8_t outputs, uint16_t period){
	
	*this->CTL &= ~PWM_STOP;
	outputs >>=1;
	
	pwm_port_enable(this, outputs);
	
	this->OUTs = outputs;	
	
	if ( PWM_UP_DOWN == counter_mode)
		*this->_CCR0 = period >> 1; 
	if ( PWM_UP == counter_mode)
		*this->_CCR0 = period - 1; 
	
	*this->CTL  = clock_source + counter_mode; // + TACLR; 
  
}

void pwm_disable(pwm_handle this){
	*this->CTL &= ~PWM_STOP;
}

void pwm_set(pwm_handle this, uint8_t cc_id, uint16_t cc_cnt, uint16_t cc_mode){
	
	*this->CCR[cc_id] = cc_cnt; 
	*this->CCTL[cc_id] = cc_mode; 
	
}


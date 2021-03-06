
#include <msp430.h>
#include <stdlib.h>

#include "timer.h"
#include "timer_obj.h"

extern const unsigned int TIOV;

void timer_init(timer_handle this, uint16_t clkSrc, uint16_t period){
	// only up and continous
	if (period){
		*this -> CTL = clkSrc + MC_1;
		*this -> CCR0 = period;
	}
	else {
		*this -> CTL = clkSrc + MC_2;
	}
}

void timer_interrupt_enable(timer_handle this){
	*this -> CTL |= this -> TIE;
}
void timer_interrupt_disable(timer_handle this){
	*this -> CTL &= ~this -> TIE;
}

int16_t timer_event_callbackHandler(uint16_t vector, int16_t ctr){
	if ((vector & 0xff) == TIOV){
		uint8_t i,j;
		event_handle ev;
		for (i = 0;i<_TIMER_CNT;i++) if ((vector >> 8)== _TIMER_TABLE[i].OV_ISR_vector){
			for (j = 0;j<_TIMER_TABLE[i].event_cnt;j++){
				ev = &(_TIMER_TABLE[i].events[j]);
				if (ev->enable){
					ev->counter ++;
					if (ev->period <= ev->counter){
						ev->callback(ev->call_counter);
						ev->counter = 0;
						ev->call_counter++;
					}
				}
			}
			break;
		}
	}
	return 0;
}


isr_callback_16 timer_event_callbackPreset[] = { timer_event_callbackHandler, NULL};

isr_callback_16 *timer_event_set(timer_handle this, uint8_t event_cnt, event_handle events){
	// assign to TIMERX_ISR_callbacks will overide Timerx_X1_ISR_callbacks settings
	this->event_cnt = event_cnt;
	this->events = events;

	timer_interrupt_enable(this);
	return  timer_event_callbackPreset;
}

void timer_env_set(uint8_t global_timer_count, timer_handle global_timerTable){

	_TIMER_CNT = global_timer_count;
	_TIMER_TABLE = global_timerTable;
}

void timer_event_reset(timer_handle this){
	this -> event_cnt = 0;
// 	*(this->OV_ISR_callbacks) = NULL;
}


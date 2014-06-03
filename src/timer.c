
#include <msp430.h>
#include <stdlib.h>

#include "timer.h"
#include "timer_obj.h"



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
					if (ev->period == ev->counter){
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


_ISR_callback_16 timer_event_callbackPreset[] = { timer_event_callbackHandler, NULL};

void timer_event_set(timer_handle this, uint8_t event_cnt, event_handle events){
	// this will overide Timerx_X1_ISR_callbacks settings
	this->event_cnt = event_cnt;
	this->events = events;

	*(this->OV_ISR_callbacks) = timer_event_callbackPreset;
	timer_interrupt_enable(this);
}

void timer_env_set(uint8_t global_timer_count, timer_handle global_timerTable){

	_TIMER_CNT = global_timer_count;
	_TIMER_TABLE = global_timerTable;
}

void timer_event_reset(timer_handle this){
	this -> event_cnt = 0;
// 	*(this->OV_ISR_callbacks) = NULL;
}


/*void timer_event_init(timer_handle this){
	// this will overide Timerx_X1_ISR_callbacks settings
	this->events = (event_handle)malloc(sizeof(event_handle)*EVENT_ALLOC_INCREMENT);
	*this->OV_ISR_callbacks = (*_ISR_callback_16)malloc(sizeof(*_ISR_callback_16)*EVENT_ALLOC_INCREMENT);
	this->event_count = 0;
	timer_interrupt_enable(this);
}


void timer_event_add(timer_handle this, event_handle event){

	this->events[this->event_count] = event;
	(*this->OV_ISR_callbacks)[this->event_count] = event->callback;

	this->event_count ++;
}
*this -> events = event_list;
//	this->ISR_callbacks = (*_ISR_callback_16)malloc(sizeof(_ISR_callback_16) * _ISR_callback_16);


}*/

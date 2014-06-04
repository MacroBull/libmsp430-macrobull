
#ifndef __TIMER_OBJ_H
#define __TIMER_OBJ_H

#include <msp430.h>
#include <stdlib.h>

#include "hw_obj.h"
#include "isr_wrapper.h"

#define TIOV 14


typedef void (*timer_event_callback)(uint16_t call_counter);

typedef struct event_struct {
	
// 	struct event_struct *next;
	
	uint8_t enable;
	uint16_t ISR_vector;
	uint16_t period, counter, call_counter;
	
	timer_event_callback callback;
	
} event_obj;

typedef event_obj *event_handle;


typedef struct {
	const addr16 CTL;
	const addr16 CCR0;
	
	const uint16_t TIE;
	
	const uint16_t OV_ISR_vector;
	
	uint8_t event_cnt;
	event_handle events;
	
} timer_obj;

typedef timer_obj *timer_handle;

uint8_t _TIMER_CNT;
timer_handle _TIMER_TABLE;

#endif

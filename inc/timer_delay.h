
#ifndef __TIMER_DELAY_H
#define __TIMER_DELAY_H

#include <msp430.h>
#include <stdlib.h>

#include "timer_obj.h"


extern uint16_t timer_delay_counter;
extern isr_callback_16 *prev_list;

extern void timer_delay(isr_callback_16 * list, uint16_t delay);

#endif

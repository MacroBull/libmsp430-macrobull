
#ifndef __TIMER_H
#define __TIMER_H

#include <msp430.h>
#include <stdlib.h>

#include "timer_obj.h"

#define TSRC_TACLK	TASSEL_0
#define TSRC_ACLK	TASSEL_1
#define TSRC_SMCLK	TASSEL_2
#define TSRC_INCLK	TASSEL_2

extern void timer_init(timer_handle this, uint16_t clkSrc, uint16_t period);

extern void timer_interrupt_enable(timer_handle this);
extern void timer_interrupt_disable(timer_handle this);

extern int16_t timer_event_callbackHandler(uint16_t vector, int16_t ctr);

extern void timer_event_set(timer_handle this, uint8_t event_cnt, event_handle events);
extern void timer_event_reset(timer_handle this);
extern void timer_env_set(uint8_t global_timer_count, timer_handle global_timerTable);

#endif


#include <msp430.h>
// #include <legacymsp430.h>
#include <stdlib.h>

#include "timer.h"
#include "timer_obj.h"

uint16_t _timer_delay_counter, _R2_backup;

int16_t timer_delay_callbackHandler(uint16_t vector, int16_t ctr){
	_timer_delay_counter--;
	if (_timer_delay_counter) return 0;
	else return -CPUOFF;
}

isr_callback_16 timer_delay_callbackPreset[] = { timer_delay_callbackHandler, 
NULL};

void timer_delay(isr_callback_16 * list, uint16_t delay){
	isr_callback_16 *prev_list;
	prev_list = list;
	list = timer_delay_callbackPreset;
	_timer_delay_counter = delay;
	_R2_backup = READ_SR();
	_BIS_SR(CPUOFF + GIE);
	WRITE_SR(_R2_backup);
	list = prev_list;
}


#ifndef __RANDOM_H
#define __RANDOM_H

#include <msp430.h>
#include <stdint.h>

#if defined(__MSP430_HAS_ADC12__) || defined(__MSP430_HAS_ADC12_PLUS__)
extern uint16_t rand_fromADC();
#endif


#ifdef __MSP430_HAS_UCS__
#include "pwm/pwm_obj.h"
extern uint16_t rand_fromVLO(pwm_handle TA);
#else
extern uint16_t rand_fromVLO();
#endif

#endif

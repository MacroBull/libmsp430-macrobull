
#ifndef __RANDOM_H
#define __RANDOM_H

#include <msp430.h>
#include <stdint.h>

#include "arch.h"

#if defined(__MSP430_HAS_ADC10__) || defined(__MSP430_HAS_ADC10_PLUS__) || defined(__MSP430_HAS_ADC12__) || defined(__MSP430_HAS_ADC12_PLUS__)
extern uint_ws rand_fromADC();
#endif


#ifdef __MSP430_HAS_UCS__
#include "pwm/pwm_obj.h"
extern uint_ws rand_fromVLO(pwm_handle TA);
#else
extern uint_ws rand_fromVLO();
#endif

#endif

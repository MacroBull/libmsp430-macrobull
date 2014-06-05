
#ifndef __PWM_H
#define __PWM_H


#include <msp430.h>
#include <stdint.h>

#include "pwm/pwm_obj.h"


#define PWM_STOP	MC_0
#define PWM_UP		MC_1
#define PWM_CONT	MC_2
#define PWM_UP_DOWN	MC_3

#define PWMSRC_TACLK	TASSEL_0
#define PWMSRC_TBCLK	TBSSEL_0

#define PWMSRC_ACLK	TASSEL_1
#define PWMSRC_SMCLK	TASSEL_2
#define PWMSRC_INCLK	TASSEL_3

#define PWM_POUT	OUTMOD_7 // +duty%
#define PWM_NOUT	OUTMOD_2 // -duty%
#define PWM_TOGGLE	OUTMOD_4 // -duty%

extern inline void pwm_port_enable(pwm_handle this, uint8_t outputs);
extern void pwm_enable(pwm_handle this, uint16_t clock_source, char counter_mode, uint8_t outputs, uint16_t period);
extern void pwm_disable(pwm_handle this);
extern void pwm_set(pwm_handle this, uint8_t cc_id, uint16_t cc_period, uint16_t cc_mode);

#endif


#ifndef __ADC10_H
#define __ADC10_H

#include	<msp430.h>
#include	<stdint.h>
#include	"misc.h"

#define	ADC_REF_VSS	0
#define	ADC_REF_VCC	33
#define	ADC_REF_1V5	15
#define	ADC_REF_2V5	25
#define	ADC_REF_N	1
#define	ADC_REF_E	2
//#define	REFNP	REFN
//#define	REFEP	10

#define	ADC_CONV_SS	0
#define	ADC_CONV_SM	1
#define	ADC_CONV_RS	2
#define	ADC_CONV_RM	3

#define	ADC_CH_TEMP 10

#define ADC10_15P	1.5/1024
#define ADC10_25P	2.5/1024

#define ADC10_BUSY	(ADC10CTL1 & ADC10BUSY)
#define ADC10_WAIT	{while(ADC10_BUSY);}


extern inline void adc10_start();
extern inline void adc10_startMSC(uint16_t *data, uint8_t len);
extern void adc10_init(uint8_t port, uint8_t sht, uint8_t refP, uint8_t refN, uint8_t startSource, uint8_t convMode);
extern void adc10_down();

extern uint16_t adc10_result();
extern uint16_t adc10_result_2s();
extern inline void avgFilter(int a[],char len, char cnt);


#endif
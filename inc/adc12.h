
#ifndef __ADC12_H
#define __ADC12_H

#include <msp430.h>
#include <stdint.h>

#define ASRC_ADC	0
#define ASRC_ACLK	1
#define ASRC_MCLK	2
#define ASRC_SMCLK	3

#define ADC_CONV_SS	0x00
#define ADC_CONV_SM	0x20
#define ADC_CONV_RS	0x40
#define ADC_CONV_RM	0x60

#define ADC_REF_VSS	0
#define ADC_REF_EN	5
#define ADC_REF_EP	10
#define ADC_REF_1V5	15
#define ADC_REF_2V5	25
#define ADC_REF_VCC	33

#define ADC_CH_EP	8
#define ADC_CH_EN	9
#define ADC_CH_TEMP	10
#define ADC_CH_HV	11
#define ADC_CH_BAT	12


extern volatile uint16_t *ADC12_RESULT;

extern int16_t adc12_result();
extern inline void adc12_start();
extern inline void adc12_ctrl_set(uint8_t rank, uint8_t channel, uint8_t refP, uint8_t refN, uint8_t enable_int);
extern void adc12_init(uint8_t resolution, uint16_t sht_L, uint16_t sht_H, uint8_t clkSrc, uint8_t convInfo);
extern void adc12_down();


#endif


#include <msp430.h>

#include "random.h"

#if defined(__MSP430_HAS_ADC10__) || defined(__MSP430_HAS_ADC10_PLUS__)
#include "adc10.h"
uint16_t rand_fromADC(){ // unfinished

// 	adc10_ctrl_set(0, ADC_CH_TEMP, 15, 0, 0); // Temperature, 1.5V ref
// 	adc10_init(10, 16, 0, ASRC_ADC, ADC_CONV_SS + 1);
	// Resolution = 10bit, SHT = 200clks, Single chanel

	uint8_t i = 16;
	uint16_t res = 0;
	while (--i){
		adc10_start();
		res <<= 1;
		res |= 1 & adc10_result();
	}
	adc10_down();
	return res;
	
}
#endif

#if defined(__MSP430_HAS_ADC12__) || defined(__MSP430_HAS_ADC12_PLUS__)
#include "adc12.h"
uint16_t rand_fromADC(){ // about 9600 clks @10MHz (sht=200) //using Temperature ADC

	adc12_ctrl_set(0, ADC_CH_TEMP, 15, 0, 0); // Temperature, 1.5V ref
	adc12_init(12, 16, 0, ASRC_ADC, ADC_CONV_SS + 1);
	// Resolution = 12bit, SHT = 200clks, Single chanel

	uint8_t i = 16;
	uint16_t res = 0;
	do{
		adc12_start();
		res <<= 1;
		res |= 1 & adc12_result();
	}while(--i);
	adc12_down();
	return res;
	
}
#endif


#ifdef __MSP430_HAS_UCS__
#include "pwm/pwm_obj.h"
uint16_t rand_fromVLO(pwm_handle TA){ // about 8500 clks @10MHz // using VLO x DCO (-> REF)
	/*
	 * This suppose to use TimerA because TAx.2 - CCI_B = TACLK,
	 * Using Timer/CC configuration from pwm_obj.h
	 */
	#define CC_ACLK 2
	uint16_t prev_UCSCTL4 = UCSCTL4;
	uint16_t prev_TACTL = *TA->CTL;
	uint16_t *TACCTL_ptr = TA->CCTL[CC_ACLK];
	uint16_t prev_TACCTL = *TACCTL_ptr;
	uint16_t prev_TACCR = *TA->CCR[CC_ACLK];
	
	UCSCTL4 = SELA_1 +  (UCSCTL4 & 0xff);  // ACLK = VLO
	*TA->CTL = TASSEL_2 + MC_2;  // TA SRC = SMCLK
	*TACCTL_ptr = CM_3 + CCIS_1 + CAP; // TACCR capture ACLK
	
	uint8_t i = 16;
	uint16_t res = 0;
	do{
		*TACCTL_ptr &= ~CCIFG;
		res <<= 1;
		while (!(CCIFG & (*TACCTL_ptr)));
		res |= 1 & *TA->CCR[CC_ACLK];
	}while (--i);
	
	/* restore settings */
	UCSCTL4 = prev_UCSCTL4;
	*TA->CTL = prev_TACTL;
	*TACCTL_ptr = prev_TACCTL;
	*TA->CCR[CC_ACLK] = prev_TACCR;
	
	return res;
	
}
#endif
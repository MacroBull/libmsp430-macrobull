
#include <msp430.h>

#include "random.h"

#if defined(__MSP430_HAS_ADC10__) || defined(__MSP430_HAS_ADC10_PLUS__)
#include "adc10.h"
uint_ws rand_fromADC(){ // unfinished

	adc10_init(ADC_CH_TEMP, 16, 15, 0, 0, ADC_CONV_SS);
	//Single chanel

	uint8_t i = ARCH_CPU_WORDSIZE;
	uint_ws res = 0;
	do{
		adc10_start();
		res <<= 1;
		res |= 1 & adc10_result();
	} while (--i);
	adc10_down();
	return res;
	
}
#endif

#if defined(__MSP430_HAS_ADC12__) || defined(__MSP430_HAS_ADC12_PLUS__)
#include "adc12.h"
uint_ws rand_fromADC(){ // about 9600 clks @10MHz (sht=200) //using Temperature ADC

	adc12_ctrl_set(0, ADC_CH_TEMP, 15, 0, 0); // Temperature, 1.5V ref
	adc12_init(12, 16, 0, ASRC_ADC, ADC_CONV_SS + 1);
	// Resolution = 12bit, SHT = 200clks, Single chanel

	uint8_t i = ARCH_CPU_WORDSIZE;
	uint_ws res = 0;
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
#include "hw_obj.h"
uint_ws rand_fromVLO(pwm_handle TA){ // about 8500 clks @10MHz // using VLO x DCO (-> REF)
	/*
	 * This suppose to use TimerA because TAx.2 - CCI_B = TACLK,
	 * Using Timer/CC configuration from pwm_obj.h
	 */
	#define CC_ACLK 2
	uint16_t prev_UCSCTL4 = UCSCTL4;
	uint16_t prev_TACTL = *TA->CTL;
	addr16 TACCTL_ptr = TA->CCTL[CC_ACLK];
	
	UCSCTL4 = SELA_1 +  (UCSCTL4 & 0xff);  // ACLK = VLO
	*TA->CTL = TASSEL_2 + MC_2;  // TA SRC = SMCLK
	*TACCTL_ptr = CM_3 + CCIS_1 + CAP; // TACCR capture ACLK
	
	uint8_t i = ARCH_CPU_WORDSIZE;
	uint_ws res = 0;
	do{
		*TACCTL_ptr &= ~CCIFG;
		res <<= 1;
		while (!(CCIFG & (*TACCTL_ptr)));
		res |= 1 & *TA->CCR[CC_ACLK];
	}while (--i);
	
	/* restore settings */
	UCSCTL4 = prev_UCSCTL4;
	*TA->CTL = prev_TACTL;
	
	return res;
	
}

#else
uint_ws rand_fromVLO(){ // using VLO x DCO
	
	uint16_t prev_BCSCTL1 = BCSCTL1;
	uint16_t prev_BCSCTL3 = BCSCTL3;
	uint16_t prev_TACTL = TA0CTL;
	
	BCSCTL1 &= ~XTS;
	BCSCTL3 = LFXT1S_2 + (BCSCTL3 & ~LFXT1S_3); // ACLK = VLO
	TA0CTL = TASSEL_2 + MC_2;  // TA SRC = SMCLK
	TA0CCTL0 = CM_3 + CCIS_1 + CAP; // TACCR capture ACLK
	
	uint8_t i = ARCH_CPU_WORDSIZE;
	uint_ws res = 0;
	do{
		TA0CCTL0 &= ~CCIFG;
		res <<= 1;
		while (!(CCIFG & TA0CCTL0));
		res |= 1 & TA0CCR0;
	}while (--i);
	
	/* restore settings */
	BCSCTL1 = prev_BCSCTL1;
	BCSCTL3 = prev_BCSCTL3;
	TA0CTL = prev_TACTL;
	
	return res;
	
}
#endif
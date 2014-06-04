
#include <msp430.h>
#include <stdint.h>

#include "adc12.h"

volatile uint16_t *ADC12_RESULT = &ADC12MEM0;
//volatile uint16_t *ADC12_RESULT = ADC12MEM;

inline void adc12_waitingRefSettle(){
	// deprecated function
	__delay_cycles(40);
}

int16_t adc12_result(){
	// deprecated function
	while ((ADC12CTL1 & ADC12BUSY) );
	return ADC12MEM0;
}

inline void adc12_start(){
	ADC12CTL0 |= ADC12SC;
}

inline void adc12_ctrl_set(uint8_t rank, uint8_t channel, uint8_t refP, uint8_t refN, uint8_t enable_int){
	/* write setting into ADC12MCTL[rank]*/
	*(&ADC12MCTL0 + rank) = channel +
		((refN>0) ? BIT6 : 0) + ((refP == ADC_REF_EP) ? BIT5 : 0) + ((refP == ADC_REF_VCC) ? 0 : BIT4);
	
	if (ADC_REF_2V5 == refP) ADC12CTL0 |= ADC12REF2_5V;
	if ((ADC_REF_1V5 == refP) || (ADC_REF_2V5 == refP)) {
		REFCTL0 &= ~REFMSTR;
		ADC12CTL0 |= ADC12REFON;
	}
// 	if ((ADC_REF_EN == refN) || (ADC_REF_1V5 == refP) || (ADC_REF_2V5 == refP)) ADC12CTL0 |= ADC12REFON;
	
	if (enable_int) ADC12IE |= 1 << rank;
	
}

static inline uint8_t adc12_sht_calc(uint16_t sht){
	const uint16_t sht_list[] = {4, 8 ,16, 32, 64, 96, 128, 192, 256, 384, 512, 768, 1024, ~0};
	uint8_t res = 0;
	while (sht_list[res] < sht) res++;
	return res;
}

void adc12_init(uint8_t resolution, uint16_t sht_L, uint16_t sht_H, uint8_t clkSrc, uint8_t convInfo) {
	/* resolution = 8, 10, 12; convInfo = ADC_CONV_MODE + amount of channels to convert(like ADC_CONV_RM + 5)*/
	convInfo --;
 	*(&ADC12MCTL0 + (0xf & convInfo)) |= ADC12EOS;
	convInfo >>= 4;
	
	ADC12CTL0 |= (adc12_sht_calc(sht_H) << 12) + (adc12_sht_calc(sht_L) << 8)  + ADC12ON;
// 	ADC12OVIE + ADC12TOVIE

	ADC12CTL1 = ADC12SHP + ADC12DIV_0 + (clkSrc << 3) /*ADC12SSEL*/ + convInfo /* ADC12CONSEQ*/;

	ADC12CTL2 = (((resolution-8) << 3) & 0x30)/* ADC12RES*/;
// 	ADC12DF

	if (convInfo) ADC12CTL0 |= ADC12MSC;
	ADC12CTL0 |= ADC12ENC;
}

void adc12_down(){
	ADC12CTL0 &= (ADC12ON + ADC12ENC + ADC12SC);
}


// float adc12_toDegC_f(int v){
// 	return (v * adc12_15P - 0.986) / 0.00355;
// }

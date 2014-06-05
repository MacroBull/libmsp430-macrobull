
#include <msp430.h>
#include <stdint.h>

#include "adc10.h"


static inline void adc10_waitingRefSettle(){
	
	__delay_cycles(40);
}

inline void adc10_start(){
    ADC10CTL0 |= ENC + ADC10SC;
}

inline void adc10_startMSC(uint16_t *data, uint8_t len){
	ADC10DTC1 = len;  
	//__delay_cycles(40);
	ADC10SA = (uint16_t)data;
    ADC10CTL0 |= ENC + ADC10SC;
}

void adc10_init(uint8_t port, uint8_t sht, uint8_t refP, uint8_t refN, uint8_t startSource, uint8_t convMode) { // ~387~414 CLKs;
	
	uint8_t temp;
	
	//defualt clock 
	ADC10CTL0 = ADC10ON + ADC10SSEL_0 + ADC10DIV_0;
	
	ADC10CTL1 = (port << 12) /* INCH */ + (startSource  << 10) /* SHS */  + (convMode << 1) /* CONVSEQ */ ;
	
	//SHT
	temp = 0;
	sht -= 1;
	temp += (sht>>=2)>0;
	temp += (sht>>=1)>0;
	temp += (sht>>=1)>0;
	ADC10CTL0 |= temp << 11; 
	
	//MSC & CONSEQ_0  + DTC
	if (convMode) ADC10CTL0 |= MSC;
	
	if ((convMode & BIT0)){
		ADC10AE0  = ((1 << (port+1)) - 1) & 0xff;
		/* only for F22xx
		ADC10AE1  = (1 << (port-8)) - 1; 
		*/
	}
	else{
		ADC10AE0  = (1 << port) & 0xff;
		/* only for F22xx
		ADC10AE1  = 1 << (port-8); 
		*/
	}
	
	//reference on
	if (refP==ADC_REF_2V5) ADC10CTL0 |= REF2_5V;
	if (refP==ADC_REF_E) ADC10CTL0 |= REFOUT;
	if ((refN==ADC_REF_N) || (refP==ADC_REF_1V5) || (refP==ADC_REF_2V5)) {
		ADC10CTL0 |= REFON;
		//if (temp_char == 0) ADC_waitingRefSettle(); //40 cycles for ref startup
	}
	//REFVCC==0
	if ((refP==ADC_REF_1V5) || (refP==ADC_REF_2V5)) ADC10CTL0 |= SREF0;
	if (refP==ADC_REF_E) ADC10CTL0 |= SREF1;
	if (refN) ADC10CTL0 |= SREF2;
	
// 	ADC10CTL0 |= ENC;
	
} // ADC_init


void adc10_down(){
	ADC10CTL0 &= ~(ADC10ON + ENC + ADC10SC);
}
/*
float adc10_toDegC_f(int v){
	return (v * adc10_15P - 0.986) / 0.00355;
}
*/

int adc10_toDegC (int v){
	return ((v - 673) * 423) / 1024;
}

uint16_t adc10_result(){
	ADC10_WAIT;
	return ADC10MEM;
}

uint16_t adc10_result_2s(){
	ADC10_WAIT; 
	return ADC10MEM >> 6;
}


inline void avgFilter(int a[],char len, char cnt){ 
	// 813 min ~ 34547 @ 120,120
	// calc cnt from len
	uint16_t i, j, l;
	unsigned int acc;
	unsigned long s;
	i = j = acc =0;
	while (i<len){
		s = 0;
		l = i;
		acc+=len;
/*
#ifdef WDT_ENABLE
		weego;
#endif
*/
		while (i*cnt<acc) s+=a[i++];
		//a[j++]= s / (i-l);
		a[j++]= (s + ((i-l) >> 1)) / (i-l); //5/4 op
	}
}

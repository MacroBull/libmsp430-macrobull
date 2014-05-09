#include "adc12.h"

int (*ADC12_ISR_ptr)();

inline void ADC_waitingRefSettle(){
	
	__delay_cycles(40);
}

inline void ADC12_startMSC(unsigned int data[], unsigned char len){
	ADC12DTC1 = len;  
	//__delay_cycles(40);
	ADC12SA = (unsigned int)data;
    ADC12CTL0 |= ENC + ADC12SC;
}

void ADC12_init(char port, char refN, char refP, char sht, char timing_source, char convMode, int (*ADC12_done_ISR)()) { // ~387~414 CLKs;
	
	char temp_char;
	
	temp_char = ADC12CTL0 & REFON;
	
	ADC12CTL1 = INCH0 * port;
	
	//defualt clock 
	ADC12CTL0 = ADC12ON + ADC12SSEL_0 + ADC12DIV_0 ; 
	
	//timing
	ADC12CTL1 |= SHS0 * timing_source;
	
	//MSC & CONSEQ_0  + DTC
	if (convMode) {
		ADC12CTL0 |= MSC;
		ADC12CTL1 |= CONSEQ0 * convMode;
	}
	
	if ((convMode & CONV_MCH)){
		ADC12AE0  = ((1 << (port+1)) - 1) & 0xff;
		/* only for F22xx
		ADC12AE1  = (1 << (port-8)) - 1; 
		*/
	}
	else{
		ADC12AE0  = (1 << port) & 0xff;
		/* only for F22xx
		ADC12AE1  = 1 << (port-8); 
		*/
	}
	//SHT
	temp_char = 0;
	sht -= 1;
	temp_char += (sht>>=2)>0;
	temp_char += (sht>>=1)>0;
	temp_char += (sht>>=1)>0;
	ADC12CTL0 |= temp_char * ADC12SHT0; 
	
	//reference on
	if (refP==REF2_5) ADC12CTL0 |= REF2_5V;
	if (refP==REFE) ADC12CTL0 |= REFOUT;
	if ((refN==REFN) || (refP==REF1_5) || (refP==REF2_5)) {
		ADC12CTL0 |= REFON;
		//if (temp_char == 0) ADC_waitingRefSettle(); //40 cycles for ref startup
	}
	//REFVCC==0
	if ((refP==REF1_5) || (refP==REF2_5)) ADC12CTL0 |= SREF0;
	if (refP==REFE) ADC12CTL0 |= SREF1;
	if (refN) ADC12CTL0 |= SREF2;
	
	//enable interrupt
	if (ADC12_done_ISR != NULL){
		ADC12IE  = port; 
		__bis_SR_register(GIE);
		ADC12_set_ISR(ADC12_done_ISR);
	}
	else{
		ADC12_set_ISR(NULL);
	}
    //ADC12CTL0|= ENC;
	
} // ADC_init

/*
float ADC12_toDegC_f(int v){
	return (v * ADC12_15P - 0.986) / 0.00355;
}
*/

int ADC12_toDegC (int v){
	return ((v - 673) * 423) / 1024;
}

int ADC12_result(){
	while ((ADC12CTL1 & ADC12BUSY) ); 
	return ADC12MEM;
}

int ADC12_result_2s(){
	while ((ADC12CTL1 & ADC12BUSY) ); 
	return ADC12MEM >> 6;
}


inline void avgFilter(int a[],char len, char cnt){ 
	// 813 min ~ 34547 @ 120,120
	// calc cnt from len
	char i, j, l;
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

void ADC12_set_ISR(int (*ISR_ptr)()){
	ACD10_ISR_ptr = ISR_ptr;
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(){
	int exit_code;
	if(ACD10_ISR_ptr != NULL) {
		exit_code = (ACD10_ISR_ptr)();
		if (exit_code>0)
			__bis_SR_register_on_exit(exit_code);
		else if (exit_code<0)
			__bic_SR_register_on_exit(-exit_code);
	}
}

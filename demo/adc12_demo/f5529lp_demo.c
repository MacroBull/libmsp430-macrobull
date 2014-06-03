
#include <msp430.h>
#include "wdt.h"
#include "hal/perip/f5529.h"
#include "bsp/exp430f5529lp.h"

#include "ucs.h"
#include "uart.h"
#include "qput.h"
#include "qprintf.h"
#include "isr_wrapper.h"
#include "adc12.h"

int16_t f(uint16_t v){
	ADC12IFG = 0; // IFG is cleared on reading ADC12MEM
	return -CPUOFF;
}

isr_callback callback_list[] = {f, NULL};

void main(){

	WDT_DISABLE;

	P6SEL = BIT1;

	ADC12_ISR_callbacks = callback_list;

	ucs_DCOFreq_set(10000000);
	uart_init(UART1, 10000000, 9600);
	uart_XLED_enable(UART1);

	adc12_ctrl_set(0, 1, 33, 0, 0); // input channel 1: P6.1 / VCC ref
	adc12_ctrl_set(1, ADC_CH_HV, 25, 0, 0); // (VCC+VSS)/2 / 2.5V ref
	adc12_ctrl_set(2, ADC_CH_TEMP, 33, 0, 0); //temperatue / VCC ref
	adc12_ctrl_set(3, ADC_CH_TEMP, 25, 0, 1); //temperatue / 2.5V ref

	adc12_init(12,500,500,ASRC_ADC, ADC_CONV_RM + 4);
	// Resolution, SHT, Clock source, Repeat multiple 4 channels

	adc12_start(); // start convert(MSC)
	while (1){
		_BIS_SR(CPUOFF+GIE);
		int i;
		for (i=0;i<4;i++)
			qprintf(UART1, "%u ", ADC12_RESULT[i]);
		qputc(UART1,'\n');
	}
}





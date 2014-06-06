
#include <msp430.h>
#include "wdt.h"
#include "hal/perip.h"
#include "bsp/exp430f5529lp.h"

#include "timer.h"
#include "ucs.h"
#include "uart.h"
#include "qput.h"
#include "qprintf.h"
#include "isr_wrapper.h"
#include "adc12.h"
#include "data/json.h"
#include "pwm/pwm.h"

#include "webui.h"

#define CPU_FREQ 20000000
#define BAUDRATE 460800
#define EV_CNT 1000
#define EV_PERIOD  (CPU_FREQ / EV_CNT)
#define M (CPU_FREQ / 4000)
#define BUFFSIZE 2400


uint16_t len(char s[]){
	uint16_t r = 0;
	while (*s++) r++;
	return r;
}



// GET / HTTP/1.1

uint16_t request_cnt, data_start;
char request[BUFFSIZE], *path, response[BUFFSIZE];
uint16_t time = 0;

int16_t rx(uint16_t v, int8_t c){
	
	if (c=='\n') {
		request[request_cnt++] = '\n';
		request[request_cnt] = '\0';
		if (data_start)
			return -CPUOFF;
		else if (data_start == 0){
			if ('\n' == request[request_cnt - 2]) {
				data_start = request_cnt;
				return 0;
			}
			else
				return -CPUOFF;
		}
		
	}
	else if (c=='\r'){
		return 0;
	}
	else {
		request[request_cnt] = c;
		request_cnt++;
		return 0;
	}
}

void clock(uint16_t count){ // flash red LED for event 
	time ++;
	P1OUT ^= BIT0;
}

isr_callback_8 rx_list[]={rx,NULL};
event_obj event_list[] = {
	{
		.enable = 1,
		.period = EV_CNT,
		.callback = clock
	}
}; // events list, two flash events in different periods


int8_t strcmpL(const char *a, const char *b, uint16_t l){
	while ( (--l) && *a && (*(a++) == *(b++)));
	if (*a < *b) return -1;
	else if (*a > *b) return 1;
	else return 0;
}

char *getPath(char *s){
	char *p = s, *q;
	while (' ' != *p) p++;
	p++;
	q = p;
	while (' ' != *p) p++;
	*p = '\0';
	return q;
}

void getAll(){
	json_handle output, node;
	output = json_createObjectObj("Root", NULL);
	json_insertObjectObj(output, json_createIntObj("time", time),NULL);
// 	if ( UART0 -> RXIFG & *UART0->IFG )
// 		json_insertObjectObj(output, json_createIntObj("UARTRX", *UART0 -> RXBUF),NULL);
	json_insertObjectObj(output, 
		json_createIntObj("Analog0", ADC12_RESULT[0]),
		json_createIntObj("Analog1", ADC12_RESULT[1] * 14/23 + ADC12_RESULT[1] / 604),
		json_createIntObj("Analog2", ADC12_RESULT[2] * 14/23 + ADC12_RESULT[1] / 604),
		json_createIntObj("Voltage", ADC12_RESULT[3] * 11 / 9),
		json_createIntObj("Temperature", ADC12_RESULT[4] * 2 / 7 - 320),
		NULL);

	json_dump(response, output);
	json_free_rude(output);
}

void handleInput(){
	while(0 == data_start) _BIS_SR(CPUOFF+GIE);
 	//_BIS_SR(CPUOFF+GIE); 
//  	qprintf(UART1, "%u\n", data_start);
//  	qputs(UART1, &request[data_start]);
	json_handle data, target, output;
	data = json_parse(&request[data_start]);
	
	
	output = json_createObjectObj(NULL, NULL);
	target= json_objectIndex(data, "setTime"); // second
	if (NULL != target){
		time = target -> val_int;
		json_insertObjectObj(output, json_createStringObj("SetTime", "Succeeded."), NULL);
	}
	target= json_objectIndex(data, "setPWM"); //  duty = n / 10000
	if (NULL != target){
		pwm_set( PWM0, 1, target -> val_int / (10000 / M), PWM_POUT); // +duty%
		pwm_set( PWM0, 2, target -> val_int / (10000 / M), PWM_NOUT); // +duty%
		json_insertObjectObj(output, json_createStringObj("SetPWM", "Succeeded."), NULL);
	}
	target= json_objectIndex(data, "setUARTBaud");
	if (NULL != target){
		uart_init(UART0, CPU_FREQ, target -> val_int);
		json_insertObjectObj(output, json_createStringObj("setUARTBaud", "Succeeded."), NULL);
	}
	target= json_objectIndex(data, "writeUART");
	if (NULL != target){
		qputs(UART0, target -> val_tar);
		json_insertObjectObj(output, json_createStringObj("writeUART", "Succeeded."), NULL);
	}
	
 	json_dump(response, output);
	json_free_rude(data);
// 	json_free_rude(target);
 	json_free_rude(output);
}

int main(){
	
	WDT_DISABLE;
	
	P6SEL = ~0;
	
  	USCI_A1_ISR_callbacks = rx_list;
	
	ucs_DCOFreq_set(CPU_FREQ);
	uart_init(UART1, CPU_FREQ, BAUDRATE);
	uart_XLED_enable(UART1);
	uart_interrupt_enable(UART1);
	
	pwm_enable(PWM0, PWMSRC_SMCLK, PWM_UP, BIT1 + BIT2, M); // enable 4 TA0 out, up mode
	pwm_set( PWM0, 1, M >> 1, PWM_POUT); // +duty%
	pwm_set( PWM0, 2, M >> 1, PWM_NOUT); // +duty%
	
	
	adc12_ctrl_set(0, 0, 33, 0, 0); // input channel 0: P6.1 / VCC ref
	adc12_ctrl_set(1, 1, 25, 0, 0); // channel 1/ 2.5V ref
	adc12_ctrl_set(2, 2, 25, 0, 0); // channel 2/ 2.5V ref
	adc12_ctrl_set(3, ADC_CH_HV, 25, 0, 0); // (VCC+VSS)/2 / 2.5V ref
	adc12_ctrl_set(4, ADC_CH_TEMP, 25, 0, 0); //temperatue / 2.5V ref

	adc12_init(12,200,0,ASRC_ADC, ADC_CONV_RM + 5);
	// Resolution, SHT, Clock source, Repeat multiple 7 channels
	adc12_start(); // start convert(MSC)
	
	
	timer_env_set(TIMER_CNT, TIMER_TABLE); // set timer_event environment
	timer_init(TIMER2, TSRC_SMCLK, EV_PERIOD); // set timer2(Timer_A2) in period of 4000 SMCLKs
	TIMER2_A1_ISR_callbacks = timer_event_set(TIMER2, 1,  event_list); //makes timer2 in event mode
	
	P1DIR |= BIT0;
	
// 	qputs(UART1, "Inited\n");
	
	while (1){
		request_cnt = 0;
		data_start = 0;
		_BIS_SR(CPUOFF+GIE);
		
// //  		qputsln(UART1, request);
		if ( strcmpL(&request[0], "GET", 3) == 0 ){
 			path = getPath(&request[3]);
// 			qputsln(UART1, path);
			
			if ( strcmpL(path, "/", -1) == 0 ){
				qputsln(UART1, header_200);
				qprintf(UART1, "Content-Length: %d\n\n", len(_html));
				qputsln(UART1, _html);
			}
			else if ( strcmpL(path, "/read", -1) == 0 ){
				qputsln(UART1, header_200);
				getAll();
				qprintf(UART1, "Content-Length: %d\n\n", len(response));
				qputsln(UART1, response);
			}
			else {
				qputsln(UART1, header_404);
				qprintf(UART1, "Content-Length: %d\n\n", len(_html_404));
				qputsln(UART1, _html_404);
			}
			
		}
		else if ( strcmpL(&request[0], "POST", 4) == 0 ){
 			path = getPath(&request[3]);
			if ( strcmpL(path, "/write", -1) == 0 ){
				handleInput();
				qputsln(UART1, header_200);
				qprintf(UART1, "Content-Length: %d\n\n", len(response));
				qputsln(UART1, response);
			}
		}
		
	}
	
	return 0;
}


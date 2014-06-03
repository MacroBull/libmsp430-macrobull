
#include <msp430.h>
#include <stdint.h>

#include "wdt.h"
#include "hal/perip/f5529.h"
#include "bsp/exp430f5529lp.h"

#include "uart.h"
#include "qput.h"
#include "isr_wrapper.h"
#include "data/json.h"
#include "binutil/checksum/crc32.h"

int wait;
char text[2048], *p, func;
int pos;

#define PERIOD_LENGTH 256
#include "data.h"

int16_t rx_proc(const uint16_t ISR_vector, int8_t c){ // "echo" function
	
	if (wait){
		if ('\n' == c){
			return -CPUOFF;
		}
		*p++ = c;
	}
	
	return 0;
}


json_handle objTest(){
	//a(n:38)->b(me:JSON!)->c(b:xx)
	json_handle a, b, c;
	
	a = json_createIntObj("n", -38);
	b = json_createStringObj("me'", "JSON!");
	c = json_createBlobObj("b", "xx", 4);

	return json_createObjectObj("Root",a,b,c,NULL);
	
}

json_handle encode_data_demo(){
	uint32_t crc32_val;
	json_handle range_start, length, data_obj, crch, crcl;
	
	range_start = json_createIntObj("range_start", pos*2);
	length = json_createIntObj("length'", PERIOD_LENGTH);
	data_obj = json_createBlobObj("data", &data[pos], PERIOD_LENGTH);
	crc32_val = crc32_direct(0, &data[pos], PERIOD_LENGTH);
	crch = json_createIntObj("CRC32H", 0xffff & (crc32_val >> 16));
	crcl = json_createIntObj("CRC32L", 0xffff & crc32_val);
	
	return json_createObjectObj("Root",range_start, length, data_obj, crch, crcl,NULL);
	
}


isr_callback_8 rx_callbacks[]={rx_proc,NULL};

int main(void)
{
	WDT_DISABLE; 
	//BC1MSET;
	
  	USCI_A1_ISR_callbacks = rx_callbacks;
	
	uart_init(UART1, 1100000, 9600);
	uart_XLED_enable(UART1);
	uart_interrupt_enable(UART1);
	
	P1DIR &= BIT1;
	P1REN |= BIT1;
	P1OUT |= BIT1;
	
	
	json_handle a;
	while (1){
 		p = text;
 		wait = 1;
 		_BIS_SR(CPUOFF + GIE);
 		wait = 0;
 		*p = '\0';
		
 		if (P1IN & BIT1) {// Key not pressed
			if (pos<4096/2){
				a = encode_data_demo();
				pos += PERIOD_LENGTH/2;
			}
			else
				a = json_createObjectObj("root", json_createStringObj("response","done"), NULL);
		}
		else {
			pos = 0;
			a = json_createObjectObj("root", json_createStringObj("response","cleared"), NULL);
		}
 
 		json_dump(text, a);
  		json_free_rude(a);
		
		
// 		int i;
// 		qputh(_uart1, 0xff & (pos >> 8));
// 		qputh(_uart1, 0xff & (pos));
// 		qputc(_uart1,'\n');
// 		for (i=0;i<PERIOD_LENGTH/2;i++){
// 			
// 			//qputs(_uart1, " 0x");
// 			qputh(_uart1, 0xff & (data[pos+i] >> 8));
// 			qputh(_uart1, 0xff & data[pos+i]);
// 		}
// 		qputs(_uart1, "\n============\n");
// 		base64enc(text, &data[pos], PERIOD_LENGTH);
		
		
  		qputs(UART1, text);
		qputc(UART1, '\n');
		//__delay_cycles(800000);
		
		
	}
	
}

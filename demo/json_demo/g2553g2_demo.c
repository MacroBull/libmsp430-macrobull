
#include <msp430.h>
#include <stdint.h>

#include "hal/perip.h"
#include "bsp/exp430g2.h"

#include "wdt.h"
#include "calib_val.h"

#include "uart.h"
#include "qput.h"
#include "isr_wrapper.h"
#include "data/json.h"


#define BUTTON BIT3

int wait;
char text[60], *p, func;
int pos;

int16_t rx_proc(const uint16_t ISR_vector, int8_t c){ // "echo" function
	
	uart_RXLED_on(UART0);
	int ret = 0;
	if (wait){
		if ('\n' == c) ret = -CPUOFF;
		*p++ = c;
	}
	
	uart_RXLED_off(UART0);
	return ret;
}


json_handle objTest(){
	//a(n:38)->b(me:JSON!)->c(b:xx)
	json_handle a, b, c;
	
	a = json_createIntObj("n", -38);
	b = json_createStringObj("me'", "JSON!");
	c = json_createBlobObj("b", "xx", 4);

	return json_createObjectObj("Root",a,b,c,NULL);
	
}


isr_callback_8 rx_callbacks[]={rx_proc,NULL};

int main(void)
{
	WDT_DISABLE; 
	BC1MSET;
	
  	USCIAB0RX_ISR_callbacks = rx_callbacks;
	
	uart_init(UART0, 1000000, 9600);
	uart_XLED_enable(UART0);
	uart_interrupt_enable(UART0);
	
	P1DIR &= ~BUTTON;
	P1REN |= BUTTON;
	P1OUT |= BUTTON;
	
	qputs(UART0, "Inited.\n");
	
	
	json_handle a;
	while (1){
 		p = text;
 		wait = 1;
 		_BIS_SR(CPUOFF + GIE);
 		wait = 0;
 		*p = '\0';
		
 		if (P1IN & BUTTON) {// Key not pressed
			a = objTest();
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
		
		
  		qputs(UART0, text);
		qputc(UART0, '\n');
		//__delay_cycles(800000);
		
		
	}
	
}

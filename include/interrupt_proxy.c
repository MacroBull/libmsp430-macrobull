
#include "interrupt_proxy.h"


#ifdef USCIAB0RX_VECTOR
		
	USCI_UART_RX_ISR USCI_UART_RX_ISR_proxy = NULL;
	
	void USCI_UART_RX_ISR_setter(USCI_UART_RX_ISR func){
		USCI_UART_RX_ISR_proxy = func;
	}
	
	#pragma vector=USCIAB0RX_VECTOR
	__interrupt void USCI_UART_RX_ISR_implement(){
		int exit_code;
		if ( NULL != USCI_UART_RX_ISR_proxy ) {
			exit_code = USCI_UART_RX_ISR_proxy(USCIAB0RX_VECTOR, UCA0RXBUF);
		
		if (exit_code>0)
			__bis_SR_register_on_exit(exit_code);
		if (exit_code<0)
			__bic_SR_register_on_exit(-exit_code);
		}
	}
	
#endif

#ifdef USCI_A0_VECTOR
		
	static USCI_UART_RX_ISR USCI_UART_RX_ISR_proxy = NULL;
	
	void USCI_UART_RX_ISR_setter(USCI_UART_RX_ISR func){
		USCI_UART_RX_ISR_proxy = func;
	}
	
	#pragma vector=USCI_A0_VECTOR
	__interrupt void USCI_UART_RX_ISR_implement(){
		int exit_code;
		if ( NULL != USCI_UART_RX_ISR_proxy ) {
			exit_code = USCI_UART_RX_ISR_proxy(USCI_A0_VECTOR, UCA0RXBUF);
		
		if (exit_code>0)
			__bis_SR_register_on_exit(exit_code);
		if (exit_code<0)
			__bic_SR_register_on_exit(-exit_code);
		}
	}
	
#endif
	

#include "isr_wrapper.h"


//////////////////USCI_UART//////////////////////////
#ifdef USCI_A0_VECTOR

_ISR_callback_8 *USCI_A0_ISR_callbacks = NULL;
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_VECTOR_ISR_wrapper(){
	int16_t exit_code;
	_ISR_callback_8 *callback = USCI_A0_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((USCI_A0_VECTOR << 8)+ UCA0IV, UCA0RXBUF);
		callback++;
		if (exit_code>0) {
			__bis_SR_register_on_exit(exit_code);
			break;
		}
		if (exit_code<0){
			__bic_SR_register_on_exit(-exit_code);
			break;
		}
	}
}

#endif


#ifdef USCI_A1_VECTOR

_ISR_callback_8 *USCI_A1_ISR_callbacks = NULL;
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_VECTOR_ISR_wrapper(){
	int16_t exit_code;
	_ISR_callback_8 *callback = USCI_A1_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((USCI_A1_VECTOR << 8)+ UCA1IV, UCA1RXBUF);
		callback++;
		if (exit_code>0) {
			__bis_SR_register_on_exit(exit_code);
			break;
		}
		if (exit_code<0){
			__bic_SR_register_on_exit(-exit_code);
			break;
		}
	}
}

#endif
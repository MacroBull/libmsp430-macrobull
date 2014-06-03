
#include "isr_wrapper.h"


//////////////////USCI_UART//////////////////////////
#ifdef USCI_A0_VECTOR

isr_callback_8 *USCI_A0_ISR_callbacks = NULL;
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_VECTOR_ISR_wrapper(){
	int16_t exit_code;
	isr_callback_8 *callback = USCI_A0_ISR_callbacks;
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

isr_callback_8 *USCI_A1_ISR_callbacks = NULL;
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_VECTOR_ISR_wrapper(){
	int16_t exit_code;
	isr_callback_8 *callback = USCI_A1_ISR_callbacks;
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

//////////////////////Timer_A//////////////////////

#ifdef TIMER0_A0_VECTOR

isr_callback_16 *TIMER0_A0_ISR_callbacks = NULL;
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR_wrapper(void)
{
	int16_t exit_code;
	isr_callback_16 *callback = TIMER0_A0_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((TIMER0_A0_VECTOR << 8), TA0R);
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

isr_callback_16 *TIMER0_A1_ISR_callbacks = NULL;
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR_wrapper(void)
{
	int16_t exit_code;
	isr_callback_16 *callback = TIMER0_A1_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((TIMER0_A1_VECTOR << 8) + TA0IV, TA0R);
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
#ifdef TIMER1_A0_VECTOR

isr_callback_16 *TIMER1_A0_ISR_callbacks = NULL;
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR_wrapper(void)
{
	int16_t exit_code;
	isr_callback_16 *callback = TIMER1_A0_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((TIMER1_A0_VECTOR << 8), TA1R);
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

isr_callback_16 *TIMER1_A1_ISR_callbacks = NULL;
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR_wrapper(void)
{
	int16_t exit_code;
	isr_callback_16 *callback = TIMER1_A1_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((TIMER1_A1_VECTOR << 8) + TA1IV, TA0R);
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
#ifdef TIMER2_A0_VECTOR

isr_callback_16 *TIMER2_A0_ISR_callbacks = NULL;
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR_wrapper(void)
{
	int16_t exit_code;
	isr_callback_16 *callback = TIMER2_A0_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((TIMER2_A0_VECTOR << 8), TA2R);
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

isr_callback_16 *TIMER2_A1_ISR_callbacks = NULL;
#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR_wrapper(void)
{
	int16_t exit_code;
	isr_callback_16 *callback = TIMER2_A1_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((TIMER2_A1_VECTOR << 8) + TA2IV, TA0R);
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


//////////////////////Timer_B//////////////////////

#ifdef TIMERB0_VECTOR

isr_callback_16 *TIMERB0_ISR_callbacks = NULL;
#pragma vector=TIMERB0_VECTOR
__interrupt void TIMERB0_ISR_wrapper(void)
{
	int16_t exit_code;
	isr_callback_16 *callback = TIMERB0_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((TIMERB0_VECTOR << 8), TB0R);
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

isr_callback_16 *TIMERB1_ISR_callbacks = NULL;
#pragma vector=TIMERB1_VECTOR
__interrupt void TIMERB1_ISR_wrapper(void)
{
	int16_t exit_code;
	isr_callback_16 *callback = TIMERB1_ISR_callbacks;
	while (NULL != *callback){
		exit_code = (*callback)((TIMERB1_VECTOR << 8) + TB0IV, TA0R);
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

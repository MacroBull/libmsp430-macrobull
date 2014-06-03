#include <msp430.h>
#include <stdint.h>
#include "ucs.h"


void coreVLevel_set(uint8_t level)
{
	// Open PMM registers for write
	PMMCTL0_H = PMMPW_H;	
	// Set SVS/SVM high side new level
	SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
	// Set SVM low side to new level
	SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
	// Wait till SVM is settled
	while ((PMMIFG & SVSMLDLYIFG) == 0);
	// Clear already set flags
	PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
	// Set VCore to new level
	PMMCTL0_L = PMMCOREV0 * level;
	// Wait till new level reached
	if ((PMMIFG & SVMLIFG))
	while ((PMMIFG & SVMLVLRIFG) == 0);
	// Set SVS/SVM low side to new level
	SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
	// Lock PMM registers for write access
	PMMCTL0_H = 0x00;
}


uint8_t ucs_DCOFreq_set(uint32_t freq){
	// support range about from 0.2MHz to 20MHz
	uint16_t flln, bsh, bcnt;
	
	flln = freq >> 15;
	bsh = flln;
	bcnt = 3;
	while (bsh>>bcnt) bcnt++;
	bcnt -=3;
	
	UCSCTL3 = SELREF_2 + FLLREFDIV_0;	//Set DCO FLL reference = REFO
	UCSCTL4 |= SELA_2;	// Set ACLK = REFO(must have)
	__bis_SR_register(SCG0);	// Disable the FLL control loop
	
	UCSCTL0 = 0x0000;
	UCSCTL1 = DCORSEL_1 * bcnt;	// Select DCO range 
	
	UCSCTL2 = FLLD_0 + flln - 1;	// Fdco = (N + 1) * FLLRef / FLL_Div
	__bic_SR_register(SCG0);	// Enable the FLL control loop
	
	while (flln--)	__delay_cycles(1023);	// Wait for stabilized
	
	bcnt = 0xff;
	do
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);	// Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;	// Clear fault flags
	}while (bcnt-- & SFRIFG1&OFIFG);	// Test oscillator fault flag
	if (0 == bcnt) 
		return 1;
	else
		return 0;
}
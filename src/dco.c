
/* @author : macrobull
 * this code is for chips with internal calibrated dco data such as msp420g2553
 * use -lm at tail for msp430-gcc math.h
 * OFFSET ~ -2.388355675
 * freq\MHz = e**(OFFSET + 0.32914381825 * RSEL + 0.00306105552 * DCO **2 + 0.04435 * DCO )
 * 
 * BCSCTL1	= XT2OFF + XTS + DIVAx2 +  RSELx4
 * DCOCTL	= DCOx3 + MODx5
 * 
 * DCO-7 -> deadzone for MOD
 * 
 * 
*/
#include	<msp430.h>
#include	<math.h> 
#include	"dco.h"

/*
#define COEFFREL1 0.32914381825
#define COEFFDCO1 0.04435
#define COEFFDCO2 0.00306105552

#define DCOCAL1M	((CALBC1_1MHZ << 8) + CALDCO_1MHZ)
#define DCOCAL8M	((CALBC1_8MHZ << 8) + CALDCO_8MHZ)
#define DCOCAL12M	((CALBC1_12MHZ << 8) + CALDCO_12MHZ)
#define DCOCAL16M	((CALBC1_16MHZ << 8) + CALDCO_16MHZ)

float dco_offset;
*/

inline float calcFreqPoly(char rsel, char dco){
	return COEFFREL1 * rsel + COEFFDCO2 * dco * dco + COEFFDCO1 * dco;
}

inline float calcFreq(char rsel, char dco){
	return expf(dco_offset +COEFFREL1 * rsel + COEFFDCO2 * dco * dco + COEFFDCO1 * dco );
}

float calcOffset(){
	float c1, c8, c12, c16;
	c1 = logf(1.0)  - calcFreqPoly(CALBC1_1MHZ & 0x0f, CALDCO_1MHZ >>5 );
	c8 = logf(8.0)  - calcFreqPoly(CALBC1_8MHZ & 0x0f, CALDCO_8MHZ >>5 );
	c12= logf(12.0) - calcFreqPoly(CALBC1_12MHZ& 0x0f, CALDCO_12MHZ>>5 );
	c16= logf(16.0) - calcFreqPoly(CALBC1_16MHZ& 0x0f, CALDCO_16MHZ>>5 );
	dco_offset = (c1 + c8 + c12 + c16)/4;
	
}
 
unsigned int calcDCO(float freq){ //0x4+ RSELx4+ DCOx3+ MODx5
	char rsel, dco, mod;
	float f0, f1;
	if (freq<=0) return DCOCAL1M;
	f0 = (logf(freq) - dco_offset - calcFreqPoly(0, 4)) / COEFFREL1;
	rsel = (char)(0.5 + f0);
	if (rsel<0) rsel = 0;
	if (rsel>15) rsel = 15;
	
	dco = 0;
	while (calcFreq(rsel,dco)<=freq) dco++;
	if (dco>7) {
		dco =7;
		mod =0;
	}
	else {
		dco-=1;
		f1=calcFreq(rsel,dco+1);
		f0=calcFreq(rsel,dco);
		mod = (int)(32.*(freq-f0)/(f1-f0));
	}
	return (rsel << 8) + (dco << 5) + mod;
}

unsigned int setDCO(float freq){
	unsigned int r;
	if (freq== 1.0 ) r = DCOCAL1M;
	else if (freq== 8.0 ) r = DCOCAL8M;
	else if (freq== 12.0) r = DCOCAL12M;
	else if (freq== 16.0) r = DCOCAL16M;
	else r=calcDCO(freq);
	BCSCTL1 &= 0xf0;
	BCSCTL1 |= (r >> 8) & 0x0f;
	DCOCTL = r & 0x00ff;
	return r;
}
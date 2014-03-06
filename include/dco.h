
#ifndef __DCO_H

	#define __DCO_H

	#define COEFFREL1 0.32914381825
	#define COEFFDCO1 0.04435
	#define COEFFDCO2 0.00306105552

	#define DCOCAL1M	((CALBC1_1MHZ << 8) + CALDCO_1MHZ)
	#define DCOCAL8M	((CALBC1_8MHZ << 8) + CALDCO_8MHZ)
	#define DCOCAL12M	((CALBC1_12MHZ << 8) + CALDCO_12MHZ)
	#define DCOCAL16M	((CALBC1_16MHZ << 8) + CALDCO_16MHZ)

	float dco_offset;

	extern float calcFreq(char rsel, char dco);
	extern float calcOffset();
	extern unsigned int calcDCO(float freq);
	extern unsigned int setDCO(float freq);

#endif
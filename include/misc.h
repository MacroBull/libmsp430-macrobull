
#ifndef _MISC_H
#define _MISC_H

#ifndef NULL
#define NULL 0L
#endif


#define initVLO {BCSCTL1 &= ~XTS;BCSCTL1 |= XT2OFF + DIVA_0;BCSCTL3 |= LFXT1S_2;}
	
#endif

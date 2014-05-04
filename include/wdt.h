
#ifndef __WDTL_H
#define __WDT_H


/*WDT */
#define WDT_DISABLE {WDTCTL = WDTPW | WDTHOLD;}
#define WDT_GO {WDTCTL =WDTPW + WDTCNTCL;}


/* Definitions for use with the WDT settings*/
#define WDT_DIV_ACLK_32768  (WDT_ADLY_1000)     // ACLK/32768
#define WDT_DIV_ACLK_8192   (WDT_ADLY_250)      // ACLK/8192 
#define WDT_DIV_ACLK_512    (WDT_ADLY_16)       // ACLK/512 
#define WDT_DIV_ACLK_64     (WDT_ADLY_1_9)      // ACLK/64 
#define WDT_DIV_SMCLK_32768 (WDT_MDLY_32)       // SMCLK/32768
#define WDT_DIV_SMCLK_8192  (WDT_MDLY_8)        // SMCLK/8192 
#define WDT_DIV_SMCLK_512   (WDT_MDLY_0_5)      // SMCLK/512 
#define WDT_DIV_SMCLK_64    (WDT_MDLY_0_064)    // SMCLK/64 




#endif

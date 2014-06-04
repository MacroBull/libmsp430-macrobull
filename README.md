MacroBull's MSP430 lib
===========

My MSP430 lib


* Useful JSON creating, parsing and dumping tool's to make mcu exchange data with high-level programming language interface more easily.

* 4 Timer in a same form PWM object makes PWM settings simple, with SPWM data preseted.

* Easy to use Timer setting and callbacks, support many events in various overflow * periods

* Useful binary-ascii tools: CRC32, CRC16, base64(encode).

* Code effecient and easy to use "qprint.c" printf implementation, working with UART interface profiles.

* a tiny pinosc implementation (on working).

* In-place DCO frequency parameter calculation, UCS for F5xxx/F6xxx, DCO for x2xxx.

* Easy to use ADC10 and ADC12 setup.

* Random 16 bit integer generator from ADC or VLO-DCO


----------------------

Library Demo

* I2C

* JSON

* Timer/Event

* PWM

* UART

* ADC12

* Random

All demos are tested on MSPGCC 4.7.0 and CCS 6.0.0, MSP430F5529 on EXP430F5529LP, codes are compatible with MSP430G2553 on Launchpad and MSPF5529 on EXPF5529
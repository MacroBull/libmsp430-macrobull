MacroBull's MSP430 lib
===========

My MSP430 lib


* Useful JSON creating, parsing and dumping tool's to make mcu exchange data with high-level programming language interface more easily.

* PWM object makes PWM settings simple, with SPWM data preseted.

* Useful binary-ascii tools: CRC32, CRC16, base64(encode).

* Code effecient and easy to use qprint.c printf implementation, working with UART interface profiles.

* Some tiny and simple pinosc implementation will be presented in recent.


Below is old description and will be changed to new framework (branch next?)
--------
Includes 7 segment LED, ADC10 for MSP430Gxx5x, DCO auto calculation for MSP430Gx, I2C master mode, PWM over TimerA3, uart with qput and qprintf(quick maybe).

PWM, I2C and UART are "object-oriented structed" and interface setting can be edited in <a href="include/dev.h">dev.h</a> according to hardware or application specification. It is possible to change the device or adding interface like soft uart without many edit on application codes.

I'm also trying to refine an interrupt proxy for callback funcitions from various interface so that coding would be very easy; 
<a href="demo/uart_demo.c">an demo for uart</a> works quite well now.

<a href="include/dev.h">dev.h</a> has defined some interface for Launchpad and MSP430F5529 Value Line Experience boards already.

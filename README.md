MacroBull's MSP430 lib
===========

My MSP430 lib

Includes 7 segment LED, ADC10 for MSP430Gxx5x, DCO auto calculation for MSP430Gx, I2C master mode, PWM over TimerA3, uart with qput and qprintf(quick maybe).


PWM, I2C and UART are "object-oriented structed" and interface setting can be edited in <a href="include/dev.h">dev.h</a> according to hardware or application specification. It is possible to change the device or adding interface like soft uart without many edit on application codes.

I would like to try to add VTables to structed for full functional object-oriented usage.

I'm also trying to refine an interrupt proxy for callback funcitions from various interface so that coding would be very easy; 
<a href="demo/uart_demo.c">an demo for uart</a> works quite well now.

<a href="include/dev.h">dev.h</a> has defined some interface for Launchpad and MSP430F5529 Value Line Experience boards already.

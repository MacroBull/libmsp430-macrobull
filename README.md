MacroBull的MSP430代码库
===========

包含:

* 完善易用的, 为平台优化的JSON库, 提供JSON对象创建, 释放, 插入, 数组下标查找, 对象键值查找, 字符串转换功能, 为嵌入式平台提供最低开销的JSON动态操作方法; 通过使用这一cJSON库, 免除了数据输出格式顾虑, 使嵌入式平台能直接与高级语言接口进行数据交互, 极大提升高级语言端开发效率和交互可靠性.

* ~~为平台优化的~~ 数据处理工具: CRC16, CRC32校验和; base64(编码)

* PWM配置工具, 实现了硬件PWM的启用, 禁用, 占空比设置的整合.

* 7段数码管编码头文件.

* ADC10配置工具, 实现了ADC10配置, ADC10单次转换启动, 多次转换启动, 读取结果和关闭的整合.

* ADC12配置工具, 实现了ADC12配置, ADC12转换通道控制, 转换启动, 读取结果和关闭的整合.

* DCO时钟配置工具, 对于包含简单DCO的芯片, 通过校准值拟合计算配置DCO至指定频率, 误差<15%.

* UCS时钟配置工具, 对于包含UCS的芯片, 提供内核电压等级设置和计算配置DCO至指定频率, 误差<10%.

* I2C接口操作, 包含I2C主模式下的: 接口配置, 指示LED配置, I2C连续读/写方法, I2C芯片寄存器形式的读写操作.

* 中断回调整合, 通过以中断向量和相关上下文为参数的调用绑定的回调函数队列, 通过回调函数返回值设置中断退出SP状态.

* 为平台优化的qprintf字符串格式化输出库, 提供较printf更加精简高效的, 面向UART的实现.

* MSP430专用的真随机数发生器, 熵可来自ADC(ADC10/ADC12), 或双时钟(DCO+VLO).

* I2C接口操作, 包含: SPI接口配置, 指示LED配置, 基本SPI收发方法, SPI芯片寄存器形式的读写操作.

* 定时事件工具, 通过配置硬件定时器定时计数执行指定任务.

* UART接口操作, 包括UART接口配置, 指示LED配置, 中断配置和基本收发方法.

----------------------

注意: 

	部分实现可能缺少volatile关键字, 编译使用O2, O3优化可能导致异常现象.
	
	使用例程进行测试时: MSP430G2553的ADC10出现的1较多, MSP430F5529的ADC12出现的0较多, 
	
----------------------

代码例程:

* ADC10: ~~用于MSP430G2553@Launchpad~~

* ADC12: 用于MSP430F5529@F5529LP ~~MSP430F5529@F5529EXP未测试~~

* I2C: 用于MSP430F5529@F5529LP/EXP430F5529 ~~,  MSP430G2553@Launchpad~~

* JSON: 用于MSP430F5529@F5529LP/EXP430F5529,  MSP430G2553@Launchpad

* PWM: 用于MSP430F5529@F5529LP,  MSP430G2553@Launchpad

* Random: 用于MSP430F5529@F5529LP,  MSP430G2553@Launchpad

* SPI: 用于MSP430F5529@F5529LP,  ~~MSP430G2553@Launchpad未测试~~

* Timer/Event: 用于MSP430F5529@F5529LP,  MSP430G2553@Launchpad

* UART: 用于MSP430F5529@F5529LP,  MSP430G2553@Launchpad

* Serial2sock_mixture_demo: 用于MSP430F5529@F5529LP, 综合多个外设抽象库, 通过[mcu_tool](https://github.com/MacroBull/mcu_tools)中的serial2socket可以用浏览器访问改设备并控制其外设; 将来可能会加入USB-TCP转换功能, 使web server完全运行与单片机上.

例程均在MSPGCC 4.7.0和CCS 6.0.0默认设置下测试通过.




MacroBull's MSP430 lib
===========

My MSP430 lib


* Useful JSON creating, parsing and dumping tool's to make mcu exchange data with high-level programming language interface more easily.

* 4 Timer in a same form PWM object makes PWM settings simple, with SPWM data preseted.

* Easy to use Timer setting and callbacks, support many events in various overflow * periods

* Useful binary-ascii tools: CRC32, CRC16, base64(encode).

* Code effecient and easy to use "qprint.c" printf implementation, working with UART interface profiles.

* a tiny pinosc implementation other than CTS Library (on working).

* In-place DCO frequency parameter calculation, UCS-DCO for F5xxx/F6xxx, BCS-DCO for x2xxx.

* Easy to use ADC10 and ADC12 setup.

* Random 16 bit integer generator from ADC or VLO-DCO

* TODO: support hardware CRC


----------------------

NOTICE: 
	
	ADC10 random on MSP430G2553 has more 1 however ADC12 random on MSP430F5529 has more 0 _(:3JZ)_

----------------------

Library Demo

* ADC10: ~~MSP430G2553 on Launchpad~~

* ADC12: MSP430F5529 on F5529LP ~~/EXP430F5529~~

* I2C:  MSP430F5529 on F5529LP ~~,  MSP430G2553 on Launchpad~~

* JSON: MSP430F5529 on F5529LP/EXP430F5529,  MSP430G2553 on Launchpad

* PWM: MSP430F5529 on F5529LP,  MSP430G2553 on Launchpad

* Random: MSP430F5529 on F5529LP,  MSP430G2553 on Launchpad

* Timer/Event: MSP430F5529 on F5529LP,  MSP430G2553 on Launchpad

* UART: MSP430F5529 on F5529LP,  MSP430G2553 on Launchpad

* serial2sock_mixture_demo: MSP430F5529 on F5529LP, a All-in-one test demo interacting with web browser, with the help of serial2socket(in my mcu_tools repo), making it possible to access peripherals over HTTP. What need next to do is implement TCP interface over MSP430 native USB.

All demos are tested on MSPGCC 4.7.0 and CCS 6.0.0.
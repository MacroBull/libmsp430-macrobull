

#ifndef __I2C_H
#define __I2C_H

#define _ENABLE_USCI_I2C_RX_IP

#include <msp430.h>
#include <stdint.h>
//#include "misc.h"
#include "hw_obj.h"
///#include "interrupt_proxy.h"


#define	I2C_7B	0
#define	I2C_10B	1

extern void USCI_I2C_init(USCI_I2C_info *this, uint32_t freq, uint32_t baud, char is_master);

extern void USCI_I2C_XD_enable(USCI_I2C_info *this);
extern void USCI_I2C_XLED_enable(USCI_I2C_info *this);
extern void USCI_I2C_XLED_on(USCI_I2C_info *this);
extern void USCI_I2C_XLED_off(USCI_I2C_info *this);
extern void USCI_I2C_send_nack(USCI_I2C_info *this);
extern void USCI_I2C_send_stop(USCI_I2C_info *this);
extern void USCI_I2C_send_start(USCI_I2C_info *this, char is_send);
extern void USCI_I2C_reset(USCI_I2C_info *this);
extern void USCI_I2C_set(USCI_I2C_info *this);
extern void USCI_I2C_own_addr_setter(USCI_I2C_info *this, uint16_t addr);
extern void USCI_I2C_slave_addr_setter(USCI_I2C_info *this, uint16_t addr);

extern void USCI_I2C_write(USCI_I2C_info *this, char *data, uint16_t cnt);
extern char *USCI_I2C_read(USCI_I2C_info *this, char *buf, uint16_t max_cnt);

extern char USCI_I2C_reg8_read8(USCI_I2C_info *this, char addr);
extern int USCI_I2C_reg8_read16(USCI_I2C_info *this, char addr);
extern void USCI_I2C_reg8_write8(USCI_I2C_info *this, char addr, char val);
extern void USCI_I2C_reg8_write16(USCI_I2C_info *this, char addr, int val);


extern inline void USCI_I2C__write8(USCI_I2C_info *this, char c);
extern inline char USCI_I2C__read8(USCI_I2C_info *this);
extern inline void USCI_I2C__write16(USCI_I2C_info *this, int n);
extern inline int USCI_I2C__read16(USCI_I2C_info *this);


#endif
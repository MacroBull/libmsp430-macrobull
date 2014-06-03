

#ifndef __I2C_H
#define __I2C_H

#define _ENABLE_i2c_RX_IP

#include <msp430.h>
#include <stdint.h>

#include "misc.h"
#include "i2c_obj.h"

#define	I2C_7B	0
#define	I2C_10B	1

extern void i2c_init(i2c_handle this, uint32_t freq, uint32_t baud, char is_master);

extern void i2c_XD_enable(i2c_handle this);
extern void i2c_XLED_enable(i2c_handle this);
extern void i2c_XLED_on(i2c_handle this);
extern void i2c_XLED_off(i2c_handle this);
extern void i2c_send_nack(i2c_handle this);
extern void i2c_send_stop(i2c_handle this);
extern void i2c_send_start(i2c_handle this, char is_send);
extern void i2c_reset(i2c_handle this);
extern void i2c_set(i2c_handle this);
extern void i2c_own_addr_setter(i2c_handle this, uint16_t addr);
extern void i2c_slave_addr_setter(i2c_handle this, uint16_t addr);

extern void i2c_write(i2c_handle this, char *data, uint16_t cnt);
extern char *i2c_read(i2c_handle this, char *buf, uint16_t max_cnt);

extern char i2c_reg8_read8(i2c_handle this, char addr);
extern int i2c_reg8_read16(i2c_handle this, char addr);
extern void i2c_reg8_write8(i2c_handle this, char addr, char val);
extern void i2c_reg8_write16(i2c_handle this, char addr, int val);


extern inline void i2c__write8(i2c_handle this, char c);
extern inline char i2c__read8(i2c_handle this);
extern inline void i2c__write16(i2c_handle this, int n);
extern inline int i2c__read16(i2c_handle this);


#endif

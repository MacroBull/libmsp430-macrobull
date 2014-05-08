#include <stdint.h>


#ifndef __CRC16_H
#define __CRC16_H

//#define __CRC16_DISABLE_TABLE

#define CRC16_POLYNOMIAL 0x1021
/*
 * CRC-16-CCITT
 * 
 */


#ifdef __CRC16_DISABLE_TABLE

extern uint16_t crc16_direct(uint16_t crc, const char *buf, uint16_t len);

#define crc16 crc16_direct

#else

extern uint16_t digital_update_crc16(uint16_t crc, const char *data, uint16_t len);

extern uint16_t crc16_lookup(uint16_t crc, const char *buf, uint16_t len);

#define crc16 crc16_lookup

#endif

#endif

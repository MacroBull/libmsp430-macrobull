#include <stdint.h>


#ifndef __CRC32_H
#define __CRC32_H


#include "arch.h"

#define __CRC32_DISABLE_TABLE

#define CRC32_POLYNOMIAL 0xEDB88320L
/*
 * CRC-32-IEEE 802.3
 * 
 * #0x04C11DB7 or 0xEDB88320 (0x82608EDB [9])
 * 
 */


#ifdef __CRC32_DISABLE_TABLE

extern uint32_t crc32_direct(uint32_t crc, const char *buf, uint_ws len);

#define crc32 crc32_direct

#else

extern uint32_t digital_update_crc32(uint32_t crc, const char *data, uint_ws len);

extern uint32_t crc32_lookup(uint32_t crc, const char *buf, uint_ws len);

#define crc32 crc32_lookup

#endif

#endif

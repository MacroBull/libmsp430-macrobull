
#ifndef __HW_OBJ_H
#define __HW_OBJ_H

#include <stdint.h>

#include "arch.h"
#include "misc.h"

typedef volatile char *addr8; // Little Endian no problem
typedef addr8 addr; // Little Endian no problem
typedef volatile int *addr16; // Little Endian no problem

typedef const uint16_t ISR_VECTOR; 


typedef void (*_PERIP_CTL_FUNC)(void *obj);


#endif

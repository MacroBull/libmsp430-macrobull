
#include <stdint.h>

static const uint8_t base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


uint16_t base64enc(uint8_t *buf, const uint8_t *s, uint16_t len){ // buff should be pre-allocated 4/3 sizeof s
	
	// non - RFC 822
	
	uint8_t *tailPos, *bufStart;
	uint8_t t0, t1, t2;
	
	bufStart = buf;
	tailPos = (uint8_t *)s + len / 3 * 3;
	
	while (s<tailPos){
		t0 = *(s++);
		*(buf++) = base64Table[t0 >>2];
		t0 = (t0 & 0x3) << 4;
		t1 = *(s++);
		*(buf++) = base64Table[t0 + (t1 >> 4)];
		t1 = (t1 & 0xf) << 2;
		t2 = *(s++);
		*(buf++) = base64Table[t1 + (t2 >> 6)];
		*(buf++) = base64Table[t2 & 0x3f];
	};
	
	len = len % 3;
	
	if (2 == len){
		t0 = *(s++);
		*(buf++) = base64Table[t0 >>2];
		t0 = (t0 & 0x3) << 4;
		t1 = *(s++);
		*(buf++) = base64Table[t0 + (t1 >> 4)];
		t1 = (t1 & 0xf) << 2;
		t2 = 0;
		*(buf++) = base64Table[t1 + (t2 >> 6)];
		*(buf++) = '=';
	}
	
	else if (1 == len){
		t0 = *(s++);
		*(buf++) = base64Table[t0 >>2];
		t0 = (t0 & 0x3) << 4;
		t1 = 0;
		*(buf++) = base64Table[t0 + (t1 >> 4)];
		*(buf++) = '=';
		*(buf++) = '=';
	};
	
	*buf = '\0';
		
	return (buf - bufStart);
	
}

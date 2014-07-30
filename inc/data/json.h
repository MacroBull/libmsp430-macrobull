

#ifndef __JSON_H
#define __JSON_H

#include <msp430.h>
#include <stdint.h>

#include <stdlib.h>
#include <stdarg.h>

#include "binutil/base64.h"

#define CASE_JSON_END_CHARS case '\0':case ',':case '}':case ']'
#define CASE_JSON_ESCAPE_CHARS case ' ':case '\t':case '\r':case '\n'
#define CASE_JSON_NUM_CHARS case '-':case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9'

extern inline char *strcpyR(char *dest, const char *source);

extern inline char *itoa10R(char *buf, int16_t num);

//extern inline void json_clearify(char *s);

#define JSON_NULL_PTR	0L
/* value /type */
#define JSON_NULL	0
#define JSON_INT	1
#define JSON_STRING	2
#define JSON_BLOB	3

#define JSON_FALSE	0x40
#define JSON_TRUE	0x41

/* attribute/role*/
#define JSON_IN_OBJECT	0x10
#define JSON_IN_ARRAY	0x20

#define JSON_OBJECT	0x40
#define JSON_ARRAY	0x80

/* mask for attr and val */
#define JSON_VAL_MASK 0x0f
#define JSON_ATTR_MASK 0xf0


typedef struct json_struct {
	
	struct json_struct *next;

	uint8_t type;		/* The type of the item, as above. */

	int16_t val_int;	/* The item's int number, or the length of blob, if it is */
	void *val_tar;		/* The target: string, blob or child */
	
	char *name;			/* The item's name string. */
	
} json_obj;

typedef json_obj *json_handle;

extern json_handle json_createValueObj(char *name, uint8_t type);

extern json_handle json_createIntObj(char *name, int16_t num);

extern json_handle json_createStringObj(char *name, char *string);

extern json_handle json_createBlobObj(char *name, uint8_t *blob, int16_t len);

extern json_handle json_createArrayObj(char *name, ...);

extern json_handle json_createObjectObj(char *name, ...);

extern void json_insertArrayObj(json_handle this, ...);

extern void json_insertObjectObj(json_handle this, ...);

extern uint16_t json_free(json_handle obj);
extern uint16_t json_free_rude(json_handle obj);

extern json_handle json_arrayIndex(json_handle obj, uint16_t index);

extern json_handle json_objectIndex(json_handle obj, char *name);

extern uint16_t json_dump(char *buf, json_handle jObj);

extern char *json_parseR(json_handle this, char *s);

extern json_handle json_parse(char *s);


#endif



#ifndef __JSON_H
#define __JSON_H

#include <msp430.h>
#include <stdint.h>

#include <stdlib.h>

#include "binutil/base64.h"

#define CASE_JSON_END_CHARS case '\0':case ',':case '}':case ']'
#define CASE_JSON_ESCAPE_CHARS case ' ':case '\t':case '\r':case '\n'
#define CASE_JSON_NUM_CHARS case '-':case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9'

extern inline char *strcpyR(char *dest, const char *source);

extern inline char *itoa10R(char *buf, int16_t num);

//extern inline void json_clearify(char *s);

/* value /type */
#define JSON_NULL	1
#define JSON_INT	2
#define JSON_STRING	3
#define JSON_BLOB	4

#define JSON_TRUE	5
#define JSON_FALSE	6


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

	int16_t val_int;	/* The item's int number, if it is */
	void *val_tar;		/* The target: string, blob or child */
	
	char *name;			/* The item's name string. */
	
} json_obj;

typedef json_obj *json_handle;

extern json_handle json_CreateValueObj(char *name, uint8_t type);

extern json_handle json_CreateIntObj(char *name, int16_t num);

extern json_handle json_CreateStringObj(char *name, char *string);

extern json_handle json_CreateBlobObj(char *name, uint8_t *blob, uint16_t len);

extern json_handle json_CreateArrayObj(char *name, json_handle arr_head);

extern json_handle json_CreateObjectObj(char *name, json_handle obj_head);

extern uint16_t json_free(json_handle obj);
extern uint16_t json_free_rude(json_handle obj);

extern json_handle json_arrayIndex(json_handle head, uint16_t index);

extern json_handle json_objectIndex(json_handle head, char *name);

extern uint16_t json_dump(char *buf, json_handle jObj);

extern char *json_parseR(json_handle this, char *s);

extern json_handle json_parse(char *s);


#endif


#include "data/json.h"

inline char *strcpyR(char *dest, const char *source){ 
	//  copy string with keeping the char pointer for next operation
	while (*dest++ = *source++);
	return dest - 1;
}

inline char *itoa10R(char *buf, int16_t num){
	//  itoa base 10 with keeping the char pointer for next operation
	char tmp[5], *p_tmp;
	
	p_tmp = tmp;
	if (0 == num){
		*buf++ = '0';
	}
	else if (num < 0){
		*buf++ = '-';
		num = -num;
	};
	
	while (num){
		*(p_tmp++) = (num % 10) + '0';
		num /= 10;
	}
	
	while (p_tmp > tmp)
		*buf++ = *(--p_tmp);
	
	*buf = '\0';
	
	return buf;
}

/*
inline void json_clearify(char *s){
	
	char *t;
	while (*s){
		switch (*s){
			CASE_JSON_ESCAPE_CHARS:
				t = s+1;
				while (*t)
					*(t-1) = *t;
				break;
		}
		s++;
	}
}
*/

json_handle json_createValueObj(char *name, uint8_t type){
	// Object with type/value only
	json_handle this;
	
	this = (json_handle)malloc(sizeof(json_obj));
	
	this->next = NULL;
	this->type = type;
	this->val_int = 0; //
	this->val_tar = NULL; //
	this->name = name;
	
	return this;
}

json_handle json_createIntObj(char *name, int16_t num){
	// Object of int number
	json_handle this;
	
	this = (json_handle)malloc(sizeof(json_obj));
	
	this->next = NULL;
	this->type = JSON_INT;
	this->val_int = num;
	this->val_tar = NULL; //
	this->name = name;
	
	return this;
}

json_handle json_createStringObj(char *name, char *string){
	// Object of string
	json_handle this;
	
	this = (json_handle)malloc(sizeof(json_obj));
	
	this->next = NULL;
	this->type = JSON_STRING;
	this->val_int = 0;
	this->val_tar = string;
	this->name = name;
	
	return this;
}

json_handle json_createBlobObj(char *name, uint8_t *blob, int16_t len){
	// Object of blob with size of len
	json_handle this;
	
	this = (json_handle)malloc(sizeof(json_obj));
	
	this->next = NULL;
	this->type = JSON_BLOB;
	this->val_int = len;
	this->val_tar = blob;
	this->name = name;
	
	return this;
}

json_handle json_createArrayObj(char *name, ...){
	/* Array object from param(a0,a1,a2...NULL) (end with NULL)
	 * this->[a0,a1,a2....an]
	 */
	json_handle this, next, prev;
	va_list args;
	
	this = (json_handle)malloc(sizeof(json_obj));
	
	this->next = NULL;
	this->type = JSON_ARRAY;
	this->val_int = 0;
	this->name = name;
	
	va_start(args, name);
	prev = va_arg(args, json_handle);
	this->val_tar = prev;
	while (NULL != prev){
		prev->type |= JSON_IN_ARRAY;
		next = va_arg(args, json_handle);
		prev -> next = next;
		prev = next;
	}
	va_end(args);
	
	return this;
}

json_handle json_createObjectObj(char *name, ...){
	/* Objects from param(a0,a1,a2...NULL) (end with NULL)
	 * this->[a0,a1,a2....an]
	 */
	json_handle this, next, prev;
	va_list args;
	
	this = (json_handle)malloc(sizeof(json_obj));
	
	this->next = NULL;
	this->type = JSON_OBJECT;
	this->val_int = 0;
	this->name = name;
	
	va_start(args, name);
	prev = va_arg(args, json_handle);
	this->val_tar = prev;
	while (NULL != prev){
		prev->type |= JSON_IN_OBJECT;
		next = va_arg(args, json_handle);
		prev -> next = next;
		prev = next;
	}
	va_end(args);
	
	return this;
}

uint16_t json_free(json_handle obj){ 
	// free an json object, return the amount of object deleted.
	json_handle prev;
	uint16_t cnt = 0;
	
	while (obj){
		if (NULL != obj->name) free(obj->name);
		if ((obj->type & (JSON_OBJECT | JSON_ARRAY)) && (NULL != obj -> val_tar)) // crawl in children
			cnt += json_free(obj->val_tar);
		prev = obj;
		obj = obj->next;
		free(prev);
		cnt++;
	}
	return cnt;
	
}

uint16_t json_free_rude(json_handle obj){ 
	// free an json object with all its infomation, be care of blob
	// return the amount of object deleted.
	json_handle prev;
	uint16_t cnt = 0;
	
	while (obj){
		if (NULL != obj->name) free(obj->name);
		if (NULL != obj -> val_tar)
			if (obj->type & (JSON_OBJECT | JSON_ARRAY)) // crawl in children
				cnt += json_free_rude(obj->val_tar);
			else
				free(obj->val_tar);
		prev = obj;
		obj = obj->next;
		free(prev);
		cnt++;
	}
	return cnt;
	
}

json_handle json_arrayIndex(json_handle obj, uint16_t index){
	// get array obj[index], return NULL if fails
	obj = obj->val_tar;
	while (NULL != obj){
		if (0 == index)
			break;
		index--;
		obj = obj->next;
	}
	return obj;
}

json_handle json_objectIndex(json_handle obj, char *name){
	// get dict obj["name"], return NULL if fails
	// no conflict checking
	obj = obj->val_tar;
	while (NULL != obj){
		if ( 0 == strcmp(name, obj->name) )
			break;
		obj = obj->next;
	}
	return obj;
}

uint16_t json_dump(char *buf, json_handle jObj){
	// dump an object to string
	char *p_buf;
	uint8_t type;
	
	p_buf = buf;
	
	while (NULL != jObj) {
		type = jObj->type;
		
		if ((type & JSON_IN_OBJECT) && (NULL != jObj->name)){
			// CAUTION : empty name would not display
			*p_buf++ = '"';
			p_buf = strcpyR(p_buf, jObj->name);
			*p_buf++ = '"';
			*p_buf++ = ':';
		};
		
		if (JSON_OBJECT & type){
			//in case of object
			*p_buf++ = '{';
			p_buf += json_dump(p_buf, jObj->val_tar);
			*p_buf++ = '}';
		}
		else if (JSON_ARRAY & type){
			//in case of array
			*p_buf++ = '[';
			p_buf += json_dump(p_buf, jObj->val_tar);
			*p_buf++ = ']';
		}
		else switch (type & JSON_VAL_MASK){
			//handling values
			case	JSON_NULL:
				p_buf = strcpyR(p_buf, "null");
				break;
			case	JSON_TRUE:
				p_buf = strcpyR(p_buf, "true");
				break;
			case	JSON_FALSE:
				p_buf = strcpyR(p_buf, "false");
				break;
			case	JSON_INT:
				p_buf = itoa10R(p_buf, jObj->val_int);
				break;
			case	JSON_STRING:
				*p_buf++ = '"';
				if (NULL != jObj->val_tar) 
					p_buf = strcpyR(p_buf, jObj->val_tar);
				*p_buf++ = '"';
				break;
			case	JSON_BLOB:
				//blob is base64 encoded
				p_buf = strcpyR(p_buf, "\"data:;base64,");
				if (NULL != jObj->val_tar) 
					p_buf += base64enc(p_buf, jObj->val_tar, jObj->val_int);
				*p_buf++ = '"';
				break;
			default:
				// hint for unhandled values
				p_buf = strcpyR(p_buf, "null");
		}
		
		jObj = (type & (JSON_IN_OBJECT | JSON_IN_ARRAY) ) ? jObj->next : NULL;
		// linked objects would be directly dumped regardless of the parent object
		if (NULL != jObj){
			*p_buf++ = ',';
		};
		
	};
	
	*p_buf = '\0';
	
	return p_buf - buf;
}


char *json_parseR(json_handle this, char *s){
	// parse string to json objects with keeping the char pointer for next operation
	char *sp_head, *p_s, c_tmp;
	json_handle tail, next;
	
	sp_head = NULL;
	while (*s){
		switch (*s){
			CASE_JSON_END_CHARS:
			if (sp_head){ // handling special values
				if (('t' == *sp_head)&&('r' == *(sp_head+1))&&
					('u' == *(sp_head+2))&&('e' == *(sp_head+3)))
					this->type = (this->type & JSON_ATTR_MASK) | JSON_TRUE;
				else if (('f' == *sp_head)&&('a' == *(sp_head+1))&&
					('l' == *(sp_head+2))&&('s' == *(sp_head+3))&&
					('e' == *(sp_head+4)))
					this->type = (this->type & JSON_ATTR_MASK) | JSON_FALSE;
				else if (('n' == *sp_head)&&('u' == *(sp_head+1))&&
					('l' == *(sp_head+2))&&('l' == *(sp_head+3)))
					this->type = (this->type & JSON_ATTR_MASK) | JSON_NULL;
			}
			return s+1;
			
			CASE_JSON_ESCAPE_CHARS:
				s++;
				break;
			
			
			case	'{': // handling object
				s++;
				tail = this;
				while ('}' != *(s-1)){
					next = json_createValueObj(NULL, JSON_NULL);
					s = json_parseR(next, s);
					tail -> next = next;
					tail = tail -> next;
					tail -> type |= JSON_IN_OBJECT;
				}
				this->next = NULL;
				this->type = (this->type & JSON_ATTR_MASK) |JSON_OBJECT;
				this->val_tar = this->next;
				break;
				
			case	'[': // handling array
				s++;
				tail = this;
				while (']' != *(s-1)){
					next = json_createValueObj(NULL, JSON_NULL);
					s = json_parseR(next, s);
					tail -> next = next;
					tail = tail -> next;
					tail -> type |= JSON_IN_ARRAY;
				}
				this->type = (this->type & JSON_ATTR_MASK) | JSON_ARRAY;
				this->val_tar = this->next;
				this->next = NULL;
				break;
				
			case	'"': // handling string / name
				this->type = (this->type & JSON_ATTR_MASK) | JSON_STRING;
				p_s = s;
				while ('"' != *(++p_s));
				this->val_tar = (char *)malloc(p_s-s);
				*p_s = '\0';
				strcpyR(this->val_tar, s+1);
				*p_s = '"';
				s = p_s +1;
				break;
				
			CASE_JSON_NUM_CHARS: // handling int number, int16_t only
				this->type = (this->type & JSON_ATTR_MASK) | JSON_INT;
				p_s = s+1;
				while ((*p_s <='9')&&(*p_s>='0')) p_s++;
				c_tmp = *p_s;
				*p_s = '\0';
				this->val_int = atoi(s);
				*p_s = c_tmp;
				s = p_s;
				break;
				
			case	':': // acknowledge of name, move from string
				this->name = this->val_tar;
				this->val_tar = NULL;
				s++;
				break;
			default: // maybe special values
				if (NULL == sp_head)
					sp_head = s;
				s++;
				break;
				
		}
	}
	
	return NULL;
}

json_handle json_parse(char *s){
	// parse string to json object
	json_handle this;
	this = json_createValueObj(NULL, JSON_NULL);
	json_parseR(this, s);
	return this;
}

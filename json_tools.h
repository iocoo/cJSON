
/************************************************************************
*
* Filename: json_tools.h
*
* Version 1,  2012/05/10,    wang gigi
*
* add: 20120722 GBK-UTF8
*************************************************************************/
#ifndef JSON_TOOLS_H_JSON
#define JSON_TOOLS_H_JSON

#ifdef __cplusplus
extern "C"
{
#endif

#include "cJSON.h"
//#include <sys/timeb.h>
#include <ctype.h>

#define J_STRING	0
#define J_NUMINT	1
#define J_LLONG		2
#define J_DOUBLE	3
#define J_ARRAY		4
#define J_OBJECT	5

extern char sBusiParams[128];
extern char strCcsOpId[32];
extern char sClientId[32];

int get_JsonValue(const char *Res_string,const char * key,char *pValue,int type);
char * get_JsonArrayValue(char *in,char **find_char, int inLen,char *out);
char * get_JsonObjectValue(char *in, char **find_char, int inLen,char *out) ;


#ifdef __cplusplus
}
#endif

#endif

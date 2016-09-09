#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

#define ARRAY_SIZE(x)  (sizeof(x)/sizeof(x[0]))

typedef enum
{
	STATUS_UNKNOWN = 0,
	STATUS_SUCCESS,
	STATUS_FAILURE	
} Status_e;

typedef enum
{
  BOOLEAN_UNKNOWN = 0,
  BOOLEAN_TRUE,
  BOOLEAN_FALSE
} Boolean_e;

typedef char char_t;

#endif
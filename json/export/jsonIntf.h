#ifndef JSONINTF_H
#define JSONINTF_H

#include <common/commontypes.h>

typedef struct json_object JsonObject_t;

typedef enum
{
  JSONTYPE_NULL = 0,
  JSONTYPE_BOOLEAN,
  JSONTYPE_DOUBLE,
  JSONTYPE_INT,
  JSONTYPE_OBJECT,
  JSONTYPE_ARRAY,
  JSONTYPE_STRING,

  JSONTYPE_SIZE
} JsonType_e;

typedef struct
{
  JsonObject_t * (*object_from_json_string)(const char_t * const str);
  const char_t * (*object_to_json_string)(JsonObject_t * obj);

  Boolean_e (*object_is_type)(JsonObject_t * obj, JsonType_e type);
  JsonType_e (*object_get_type)(JsonObject_t * obj);

  JsonObject_t * (*object_new)(void);
  void (*object_free)(JsonObject_t * obj);
  JsonObject_t * (*object_copy)(JsonObject_t * obj);
  void (*object_add)(JsonObject_t * obj, const char_t * const key, JsonObject_t * val);

  JsonObject_t * (*array_new)(void);
  void (*array_add)(JsonObject_t * obj, JsonObject_t * val);
  size_t (*array_size)(JsonObject_t * obj);
  JsonObject_t * (*array_get_idx)(JsonObject_t * obj, size_t idx);

  JsonObject_t * (*boolean_new)(Boolean_e b);
  Boolean_e (*boolean_get)(JsonObject_t * obj);

  JsonObject_t * (*int_new)(int64_t i);
  int64_t (*int_get)(JsonObject_t * obj);

  JsonObject_t * (*double_new)(double d);
  double (*double_get)(JsonObject_t * obj);

  JsonObject_t * (*string_new)(const char_t * s);
  const char_t * (*string_get)(JsonObject_t * obj);
} JsonIntf_t;

JsonIntf_t * getJsonIntf(void);

#endif

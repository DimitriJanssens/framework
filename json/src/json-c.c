#include "json.h"

#include <json-c/json_tokener.h>
#include <json-c/json_object.h>

JsonObject_t * _json_object_from_json_string(const char_t * const str)
{
  return json_tokener_parse(str);
}

const char_t * _json_object_to_json_string(JsonObject_t * obj)
{
  return json_object_to_json_string(obj);
}

static enum json_type local_type_to_jsonc(JsonType_e type)
{
  enum json_type rc = json_type_null;

  switch (type)
  {
    case JSONTYPE_NULL:
      rc = json_type_null;
      break;
    case JSONTYPE_BOOLEAN:
      rc = json_type_boolean;
      break;
    case JSONTYPE_DOUBLE:
      rc = json_type_double;
      break;
    case JSONTYPE_INT:
      rc = json_type_int;
      break;
    case JSONTYPE_OBJECT:
      rc = json_type_object;
      break;
    case JSONTYPE_ARRAY:
      rc = json_type_array;
      break;
    case JSONTYPE_STRING:
      rc = json_type_string;
      break;
    default:
      break;
  }

  return rc;
}

static JsonType_e local_type_from_jsonc(enum json_type type)
{
  JsonType_e rc = JSONTYPE_NULL;

  switch (type)
  {
    case json_type_null:
      rc = JSONTYPE_NULL;
      break;
    case json_type_boolean:
      rc = JSONTYPE_BOOLEAN;
      break;
    case json_type_double:
      rc = JSONTYPE_DOUBLE;
      break;
    case json_type_int:
      rc = JSONTYPE_INT;
      break;
    case json_type_object:
      rc = JSONTYPE_OBJECT;
      break;
    case json_type_array:
      rc = JSONTYPE_ARRAY;
      break;
    case json_type_string:
      rc = JSONTYPE_STRING;
      break;
    default:
    break;
  }

  return rc;
}

Boolean_e _json_object_is_type(JsonObject_t * obj, JsonType_e type)
{
  Boolean_e rc = BOOLEAN_FALSE;

  if(json_object_is_type(obj, local_type_to_jsonc(type)))
  {
    rc = BOOLEAN_TRUE;
  }

  return rc;
}

JsonType_e _json_object_get_type(JsonObject_t * obj)
{
  return local_type_from_jsonc(json_object_get_type(obj));
}

JsonObject_t * _json_object_new(void)
{
  return json_object_new_object();
}

void _json_object_free(JsonObject_t * obj)
{
  (void) json_object_put(obj);
}

JsonObject_t * _json_object_copy(JsonObject_t * obj)
{
  return json_object_get(obj);
}

void _json_object_add(JsonObject_t * obj, const char_t * const key, JsonObject_t * val)
{
  json_object_object_add(obj, key, val);
}

JsonObject_t * _json_array_new(void)
{
  return json_object_new_array();
}

void _json_array_add(JsonObject_t * obj, JsonObject_t * val)
{
  (void) json_object_array_add(obj, val);
}

size_t _json_array_size(JsonObject_t * obj)
{
  return (size_t) json_object_array_length(obj);
}

JsonObject_t * _json_array_get_idx(JsonObject_t * obj, size_t idx)
{
  return json_object_array_get_idx(obj, (int) idx);
}

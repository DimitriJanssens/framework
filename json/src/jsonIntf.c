#include <json/jsonIntf.h>

#include "json.h"

static JsonIntf_t intf =
{
  #ifndef UNITTESTS
  .object_from_json_string = _json_object_from_json_string,
  .object_to_json_string = _json_object_to_json_string,

  .object_is_type = _json_object_is_type,
  .object_get_type = _json_object_get_type,

  .object_new = _json_object_new,
  .object_free = _json_object_free,
  .object_copy = _json_object_copy,
  .object_add = _json_object_add,
  .object_get = _json_object_get,

  .array_new = _json_array_new,
  .array_add = _json_array_add,
  .array_size = _json_array_size,
  .array_get_idx = _json_array_get_idx,

  .boolean_new = _json_boolean_new,
  .boolean_get = _json_boolean_get,

  .int_new = _json_int_new,
  .int_get = _json_int_get,

  .double_new = _json_double_new,
  .double_get = _json_double_get,

  .string_new = _json_string_new,
  .string_get = _json_string_get,
  #else
  .object_from_json_string = NULL,
  .object_to_json_string = NULL,

  .object_is_type = NULL,
  .object_get_type = NULL,

  .object_new = NULL,
  .object_free = NULL,
  .object_copy = NULL,
  .object_add = NULL,
  .object_get = NULL,

  .array_new = NULL,
  .array_add = NULL,
  .array_size = NULL,
  .array_get_idx = NULL,

  .boolean_new = NULL,
  .boolean_get = NULL,

  .int_new = NULL,
  .int_get = NULL,

  .double_new = NULL,
  .double_get = NULL,

  .string_new = NULL,
  .string_get = NULL,
  #endif
};

JsonIntf_t * getJsonIntf(void)
{
  return &intf;
}

#include <json/jsonIntf.h>

#include "json.h"

static JsonIntf_t intf =
{
  .object_from_json_string = _json_object_from_json_string,
  .object_to_json_string = _json_object_to_json_string,

  .object_is_type = _json_object_is_type,
  .object_get_type = _json_object_get_type,

  .object_new = _json_object_new,
  .object_free = _json_object_free,
  .object_copy = _json_object_copy,
  .object_add = _json_object_add,

  .array_new = _json_array_new,
  .array_add = _json_array_add,
  .array_size = _json_array_size,
  .array_get_idx = _json_array_get_idx,
};

JsonIntf_t * getJsonIntf(void)
{
  return &intf;
}

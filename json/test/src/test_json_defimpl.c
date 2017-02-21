#include <json/jsonIntf.h>
#include "json.h"

void setDefaultJsonIntfForUnittests(void)
{
  JsonIntf_t * intf = getJsonIntf();

  intf->object_from_json_string = _json_object_from_json_string;
  intf->object_to_json_string = _json_object_to_json_string;

  intf->object_is_type = _json_object_is_type;
  intf->object_get_type = _json_object_get_type;

  intf->object_new = _json_object_new;
  intf->object_free = _json_object_free;
  intf->object_copy = _json_object_copy;
  intf->object_add = _json_object_add;
  intf->object_get = _json_object_get;

  intf->array_new = _json_array_new;
  intf->array_add = _json_array_add;
  intf->array_size = _json_array_size;
  intf->array_get_idx = _json_array_get_idx;

  intf->boolean_new = _json_boolean_new;
  intf->boolean_get = _json_boolean_get;

  intf->int_new = _json_int_new;
  intf->int_get = _json_int_get;

  intf->double_new = _json_double_new;
  intf->double_get = _json_double_get;

  intf->string_new = _json_string_new;
  intf->string_get = _json_string_get;
}

void resetDefaultJsonIntfForUnittests(void)
{
  JsonIntf_t * intf = getJsonIntf();

  intf->object_from_json_string = NULL;
  intf->object_to_json_string = NULL;

  intf->object_is_type = NULL;
  intf->object_get_type = NULL;

  intf->object_new = NULL;
  intf->object_free = NULL;
  intf->object_copy = NULL;
  intf->object_add = NULL;
  intf->object_get = NULL;

  intf->array_new = NULL;
  intf->array_add = NULL;
  intf->array_size = NULL;
  intf->array_get_idx = NULL;

  intf->boolean_new = NULL;
  intf->boolean_get = NULL;

  intf->int_new = NULL;
  intf->int_get = NULL;

  intf->double_new = NULL;
  intf->double_get = NULL;

  intf->string_new = NULL;
  intf->string_get = NULL;
}

#ifndef JSON_H
#define JSON_H

#include <json/jsonIntf.h>

JsonObject_t * _json_object_from_json_string(const char_t * const str);
const char_t * _json_object_to_json_string(JsonObject_t * obj);

Boolean_e _json_object_is_type(JsonObject_t * obj, JsonType_e type);
JsonType_e _json_object_get_type(JsonObject_t * obj);

JsonObject_t * _json_object_new(void);
void _json_object_free(JsonObject_t * obj);
JsonObject_t * _json_object_copy(JsonObject_t * obj);
void _json_object_add(JsonObject_t * obj, const char_t * const key, JsonObject_t * val);

JsonObject_t * _json_array_new(void);
void _json_array_add(JsonObject_t * obj, JsonObject_t * val);
size_t _json_array_size(JsonObject_t * obj);
JsonObject_t * _json_array_get_idx(JsonObject_t * obj, size_t idx);

#endif

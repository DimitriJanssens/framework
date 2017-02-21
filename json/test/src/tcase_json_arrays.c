#include "test_json_tcases.h"

#include <json/jsonIntf.h>

START_TEST(test_json_arrays_parse)
{
  const char_t * json_string = "{ \"array\": [ true, false, false, true ] }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_from_json_string(json_string);
  ck_assert(obj != NULL);

  JsonObject_t * obj_array = jsoni->object_get(obj, "array");
  ck_assert(obj_array != NULL);
  ck_assert(jsoni->object_is_type(obj_array, JSONTYPE_ARRAY) == BOOLEAN_TRUE);

  size_t obj_array_size = jsoni->array_size(obj_array);
  ck_assert(obj_array_size == 4);
  ck_assert(jsoni->boolean_get(jsoni->array_get_idx(obj_array, 0)) == BOOLEAN_TRUE);
  ck_assert(jsoni->boolean_get(jsoni->array_get_idx(obj_array, 1)) == BOOLEAN_FALSE);
  ck_assert(jsoni->boolean_get(jsoni->array_get_idx(obj_array, 2)) == BOOLEAN_FALSE);
  ck_assert(jsoni->boolean_get(jsoni->array_get_idx(obj_array, 3)) == BOOLEAN_TRUE);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

START_TEST(test_json_arrays_build)
{
  const char_t * json_string = "{ \"array\": [ true, false, false, true ] }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_new();
  ck_assert(obj != NULL);

  JsonObject_t * obj_array = jsoni->array_new();
  ck_assert(obj_array != NULL);

  jsoni->array_add(obj_array, jsoni->boolean_new(BOOLEAN_TRUE));
  jsoni->array_add(obj_array, jsoni->boolean_new(BOOLEAN_FALSE));
  jsoni->array_add(obj_array, jsoni->boolean_new(BOOLEAN_FALSE));
  jsoni->array_add(obj_array, jsoni->boolean_new(BOOLEAN_TRUE));

  jsoni->object_add(obj, "array", obj_array);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

TCase * tcase_json_arrays(void)
{
  TCase *tc = tcase_create("TestCase JsonIntf arrays");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, setDefaultJsonIntfForUnittests, resetDefaultJsonIntfForUnittests);

  tcase_add_test(tc, test_json_arrays_parse);
  tcase_add_test(tc, test_json_arrays_build);

  return tc;
}

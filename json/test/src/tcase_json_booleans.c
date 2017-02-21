#include "test_json_tcases.h"

#include <json/jsonIntf.h>

START_TEST(test_json_booleans_parse)
{
  const char_t * json_string = "{ \"bool true\": true, \"bool false\": false }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_from_json_string(json_string);
  ck_assert(obj != NULL);

  JsonObject_t * obj_boolean = jsoni->object_get(obj, "bool true");
  ck_assert(obj_boolean != NULL);
  ck_assert(jsoni->object_is_type(obj_boolean, JSONTYPE_BOOLEAN) == BOOLEAN_TRUE);
  ck_assert(jsoni->boolean_get(obj_boolean) == BOOLEAN_TRUE);

  obj_boolean = jsoni->object_get(obj, "bool false");
  ck_assert(obj_boolean != NULL);
  ck_assert(jsoni->object_is_type(obj_boolean, JSONTYPE_BOOLEAN) == BOOLEAN_TRUE);
  ck_assert(jsoni->boolean_get(obj_boolean) == BOOLEAN_FALSE);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

START_TEST(test_json_booleans_build)
{
  const char_t * json_string = "{ \"bool true\": true, \"bool false\": false }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_new();
  ck_assert(obj != NULL);

  JsonObject_t * obj_boolean = jsoni->boolean_new(BOOLEAN_TRUE);
  ck_assert(obj_boolean != NULL);

  jsoni->object_add(obj, "bool true", obj_boolean);

  obj_boolean = jsoni->boolean_new(BOOLEAN_FALSE);
  ck_assert(obj_boolean != NULL);

  jsoni->object_add(obj, "bool false", obj_boolean);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

TCase * tcase_json_booleans(void)
{
  TCase *tc = tcase_create("TestCase JsonIntf booleans");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, setDefaultJsonIntfForUnittests, resetDefaultJsonIntfForUnittests);

  tcase_add_test(tc, test_json_booleans_parse);
  tcase_add_test(tc, test_json_booleans_build);

  return tc;
}

#include "test_json_tcases.h"

#include <json/jsonIntf.h>

START_TEST(test_json_objects_parse)
{
  const char_t * json_string = "{ \"object\": { } }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_from_json_string(json_string);
  ck_assert(obj != NULL);

  JsonObject_t * obj_object = jsoni->object_get(obj, "object");
  ck_assert(obj_object != NULL);
  ck_assert(jsoni->object_is_type(obj_object, JSONTYPE_OBJECT) == BOOLEAN_TRUE);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

START_TEST(test_json_objects_build)
{
  const char_t * json_string = "{ \"object\": { } }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_new();
  ck_assert(obj != NULL);

  JsonObject_t * obj_object = jsoni->object_new();
  ck_assert(obj_object != NULL);

  jsoni->object_add(obj, "object", obj_object);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

START_TEST(test_json_objects_null_parse)
{
  const char_t * json_string = "{ \"object\": null }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_from_json_string(json_string);
  ck_assert(obj != NULL);

  JsonObject_t * obj_object = jsoni->object_get(obj, "object");
  ck_assert(obj_object == NULL);
  ck_assert(jsoni->object_is_type(obj_object, JSONTYPE_NULL) == BOOLEAN_TRUE);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

START_TEST(test_json_objects_null_build)
{
  const char_t * json_string = "{ \"object\": null }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_new();
  ck_assert(obj != NULL);

  JsonObject_t * obj_object = NULL;
  ck_assert(obj_object == NULL);

  jsoni->object_add(obj, "object", obj_object);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

TCase * tcase_json_objects(void)
{
  TCase *tc = tcase_create("TestCase JsonIntf objects");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, setDefaultJsonIntfForUnittests, resetDefaultJsonIntfForUnittests);

  tcase_add_test(tc, test_json_objects_parse);
  tcase_add_test(tc, test_json_objects_build);
  tcase_add_test(tc, test_json_objects_null_parse);
  tcase_add_test(tc, test_json_objects_null_build);

  return tc;
}

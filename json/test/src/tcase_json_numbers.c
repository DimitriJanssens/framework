#include "test_json_tcases.h"

#include <json/jsonIntf.h>

START_TEST(test_json_numbers_parse)
{
  const char_t * json_string = "{ \"int\": 123456, \"double\": 123.456 }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_from_json_string(json_string);
  ck_assert(obj != NULL);

  JsonObject_t * obj_int = jsoni->object_get(obj, "int");
  ck_assert(obj_int != NULL);
  ck_assert(jsoni->object_is_type(obj_int, JSONTYPE_INT) == BOOLEAN_TRUE);
  ck_assert(jsoni->int_get(obj_int) == 123456);

  JsonObject_t * obj_double = jsoni->object_get(obj, "double");
  ck_assert(obj_double != NULL);
  ck_assert(jsoni->object_is_type(obj_double, JSONTYPE_DOUBLE) == BOOLEAN_TRUE);
  ck_assert(jsoni->double_get(obj_double) == 123.456);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

START_TEST(test_json_numbers_build)
{
  const char_t * json_string = "{ \"int\": 123456, \"double\": 123.456 }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_new();
  ck_assert(obj != NULL);

  JsonObject_t * obj_int = jsoni->int_new(123456);
  ck_assert(obj_int != NULL);

  jsoni->object_add(obj, "int", obj_int);

  JsonObject_t * obj_double = jsoni->double_new(123.456);
  ck_assert(obj_double != NULL);

  jsoni->object_add(obj, "double", obj_double);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

TCase * tcase_json_numbers(void)
{
  TCase *tc = tcase_create("TestCase JsonIntf numbers");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, setDefaultJsonIntfForUnittests, resetDefaultJsonIntfForUnittests);

  tcase_add_test(tc, test_json_numbers_parse);
  tcase_add_test(tc, test_json_numbers_build);

  return tc;
}

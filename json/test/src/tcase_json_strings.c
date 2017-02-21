#include "test_json_tcases.h"

#include <json/jsonIntf.h>

START_TEST(test_json_strings_parse)
{
  const char_t * json_string = "{ \"string\": \"Hello, I am a string ...\" }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_from_json_string(json_string);
  ck_assert(obj != NULL);

  JsonObject_t * obj_string = jsoni->object_get(obj, "string");
  ck_assert(obj_string != NULL);
  ck_assert(jsoni->object_is_type(obj_string, JSONTYPE_STRING) == BOOLEAN_TRUE);
  ck_assert_str_eq(jsoni->string_get(obj_string), "Hello, I am a string ...");

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

START_TEST(test_json_strings_build)
{
  const char_t * json_string = "{ \"string\": \"Hello, I am a string ...\" }";

  const JsonIntf_t * const jsoni = getJsonIntf();

  JsonObject_t * obj = jsoni->object_new();
  ck_assert(obj != NULL);

  JsonObject_t * obj_string = jsoni->string_new("Hello, I am a string ...");
  ck_assert(obj_string != NULL);

  jsoni->object_add(obj, "string", obj_string);

  ck_assert_str_eq(json_string, jsoni->object_to_json_string(obj));

  jsoni->object_free(obj);
}
END_TEST

TCase * tcase_json_strings(void)
{
  TCase *tc = tcase_create("TestCase JsonIntf strings");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, setDefaultJsonIntfForUnittests, resetDefaultJsonIntfForUnittests);

  tcase_add_test(tc, test_json_strings_parse);
  tcase_add_test(tc, test_json_strings_build);

  return tc;
}

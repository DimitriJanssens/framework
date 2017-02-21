#include "test_json_tcases.h"

int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  Suite * s = suite_create("Suite JsonIntf");
  suite_add_tcase(s, tcase_json_numbers());
  suite_add_tcase(s, tcase_json_strings());
  suite_add_tcase(s, tcase_json_booleans());
  suite_add_tcase(s, tcase_json_objects());
  suite_add_tcase(s, tcase_json_arrays());
  suite_run("JSON", s);

  return 0;
}

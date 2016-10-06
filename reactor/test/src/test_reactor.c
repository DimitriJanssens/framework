#include "test_reactor_tcases.h"

int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  Suite * s = suite_create("Suite ReactorIntf");
  suite_add_tcase(s, tcase_reactor_channel());
  suite_add_tcase(s, tcase_reactor_reactor());
  suite_run("REACTOR", s);

  return 0;
}

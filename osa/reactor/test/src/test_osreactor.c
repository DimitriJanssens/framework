#include "test_osreactor_tcases.h"
 
int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  Suite * s = suite_create("Suite OsReactorIntf");
  suite_add_tcase(s, tcase_osreactor_channel());
  suite_add_tcase(s, tcase_osreactor_reactor());
  suite_run("OSREACTOR", s);
  
  return 0;
}
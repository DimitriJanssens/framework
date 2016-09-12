#include "test_ossignal_tcases.h"
 
int main(int argc, char const *argv[])
{
  (void) argc;
  (void) argv;

  Suite * s = suite_create("Suite OsSignalIntf");
  suite_add_tcase(s, tcase_ossignal());
  suite_run("OSSIGNAL", s);
  
  return 0;
}
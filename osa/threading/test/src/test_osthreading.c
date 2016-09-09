#include "test_osthreading_tcases.h"
 
int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;

  Suite * s = suite_create("Suite OsThreadingIntf");
  suite_add_tcase(s, tcase_osthreading_thread());
  suite_add_tcase(s, tcase_osthreading_mutex());
  suite_add_tcase(s, tcase_osthreading_condition());

	suite_run("OSTHREADING", s);
	
	return 0;
}
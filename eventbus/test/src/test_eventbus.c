#include "test_eventbus_tcases.h"
 
int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;

	Suite * s = suite_create("Suite EventBusIntf");
  suite_add_tcase(s, tcase_eventbus_bus());
  suite_add_tcase(s, tcase_eventbus_event());
	suite_run("EVENTBUS", s);
	
	return 0;
}
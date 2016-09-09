#include "test_list_tcases.h"
 
int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;

	Suite * s = suite_create("Suite ListIntf");
  suite_add_tcase(s, tcase_list_list());
  suite_add_tcase(s, tcase_list_item());
	suite_run("LIST", s);
	
	return 0;
}
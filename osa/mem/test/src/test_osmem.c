#include "test_osmem_tcases.h"
 
int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;

	Suite * s = suite_create("Suite OsMemIntf");
	suite_add_tcase(s, tcase_osmem());
	suite_run("OSMEM", s);
	
	return 0;
}
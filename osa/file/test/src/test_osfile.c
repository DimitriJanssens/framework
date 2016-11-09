#include "test_osfile_tcases.h"

int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;

	Suite * s = suite_create("Suite OsFileIntf");
	suite_add_tcase(s, tcase_osfile());
	suite_run("OSFILE", s);

	return 0;
}

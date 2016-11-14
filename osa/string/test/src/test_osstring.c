#include "test_osstring_tcases.h"

int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;

	Suite * s = suite_create("Suite OsStringIntf");
	suite_add_tcase(s, tcase_osstring());
	suite_run("OSSTRING", s);

	return 0;
}

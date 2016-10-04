#include "test_osutils_tcases.h"

int main(int argc, char const *argv[])
{
	(void) argc;
	(void) argv;

  Suite * s = suite_create("Suite OsUtilsIntf");

	suite_run("OSUTILS", s);

	return 0;
}

#include "test_osfile_helper.h"

#include <osa/osmemIntf.h>
#include <osa/osfileIntf.h>

void test_osfile_setup(void)
{
  setDefaultOsMemIntfForUnittests();
  setDefaultOsFileIntfForUnittests();
}

void test_osfile_teardown(void)
{
  resetDefaultOsFileIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();
}

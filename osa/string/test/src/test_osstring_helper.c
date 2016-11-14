#include "test_osstring_helper.h"

#include <osa/osmemIntf.h>
#include <osa/osstringIntf.h>

void test_osstring_setup(void)
{
  setDefaultOsMemIntfForUnittests();
  setDefaultOsStringIntfForUnittests();
}

void test_osstring_teardown(void)
{
  resetDefaultOsStringIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();
}

#include "test_osnet_helper.h"

#include <osa/osmemIntf.h>

void test_osnet_setup(void)
{
  setDefaultOsMemIntfForUnittests();
  setDefaultOsNetIntfForUnittests();
}

void test_osnet_teardown(void)
{
  resetDefaultOsNetIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();
}
#include "test_osthreading_helper.h"

#include <osa/osmemIntf.h>

#include "osthreading.h"

void test_osthreading_setup(void)
{
  setDefaultOsMemIntfForUnittests();
  setDefaultOsThreadingIntfForUnittests();
}

void test_osthreading_teardown(void)
{
  resetDefaultOsThreadingIntfForUnittests();
  setDefaultOsMemIntfForUnittests();
}

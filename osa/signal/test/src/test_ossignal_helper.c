#include "test_ossignal_helper.h"

#include <osa/osmemIntf.h>

void test_ossignal_setup(void)
{
  setDefaultOsMemIntfForUnittests();

  setDefaultOsSignalIntfForUnittests();
}

void test_ossignal_teardown(void)
{
  resetDefaultOsSignalIntfForUnittests();

  resetDefaultOsMemIntfForUnittests();
}
#include "test_osreactor_helper.h"

#include <osa/osmemIntf.h>
#include <osa/osnetIntf.h>
#include <osa/osthreadingIntf.h>
#include <collection/listIntf.h>

void test_osreactor_setup(void)
{
  setDefaultOsMemIntfForUnittests();
  setDefaultOsReactorIntfForUnittests();
  setDefaultOsNetIntfForUnittests();
  setDefaultOsThreadingIntfForUnittests();
  setDefaultListIntfForUnittests();
}

void test_osreactor_teardown(void)
{
  resetDefaultListIntfForUnittests();
  resetDefaultOsThreadingIntfForUnittests();
  resetDefaultOsNetIntfForUnittests();
  resetDefaultOsReactorIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();
}
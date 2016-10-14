#include "test_eventbus_helper.h"

#include <osa/osmemIntf.h>
#include <collection/listIntf.h>
#include <osa/osthreadingIntf.h>
#include <osa/osutilsIntf.h>

#include "eventbus.h"

void test_eventbus_setup(void)
{
  setDefaultEventBusIntfForUnittests();

  setDefaultOsMemIntfForUnittests();
  setDefaultListIntfForUnittests();
  setDefaultOsThreadingIntfForUnittests();
  setDefaultOsUtilsIntfForUnittests();
}

void test_eventbus_teardown(void)
{
  resetDefaultOsUtilsIntfForUnittests();
  resetDefaultOsThreadingIntfForUnittests();
  resetDefaultListIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();

  resetDefaultEventBusIntfForUnittests();
}

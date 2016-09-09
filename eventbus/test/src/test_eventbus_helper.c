#include "test_eventbus_helper.h"

#include <osa/osmemIntf.h>
#include <collection/listIntf.h>
#include <osa/osthreadingIntf.h>

#include "eventbus.h"

void test_eventbus_setup(void)
{
  setDefaultEventBusIntfForUnittests();

  setDefaultOsMemIntfForUnittests();
  setDefaultListIntfForUnittests();
  setDefaultOsThreadingIntfForUnittests();
}

void test_eventbus_teardown(void)
{
  resetDefaultOsThreadingIntfForUnittests();
  resetDefaultListIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();

  resetDefaultEventBusIntfForUnittests();
}
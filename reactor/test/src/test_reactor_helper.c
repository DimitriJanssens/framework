#include "test_reactor_helper.h"

#include <osa/osmemIntf.h>
#include <osa/osnetIntf.h>
#include <osa/osthreadingIntf.h>
#include <collection/listIntf.h>
#include <osa/osepollIntf.h>

void test_reactor_setup(void)
{
  setDefaultOsMemIntfForUnittests();
  setDefaultReactorIntfForUnittests();
  setDefaultOsNetIntfForUnittests();
  setDefaultOsThreadingIntfForUnittests();
  setDefaultListIntfForUnittests();
  setDefaultOsEpollIntfForUnittests();
}

void test_reactor_teardown(void)
{
  resetDefaultOsEpollIntfForUnittests();
  resetDefaultListIntfForUnittests();
  resetDefaultOsThreadingIntfForUnittests();
  resetDefaultOsNetIntfForUnittests();
  resetDefaultReactorIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();
}

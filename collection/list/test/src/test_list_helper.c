#include "test_list_helper.h"

#include <osa/osmemIntf.h>

#include "list.h"

void test_list_setup(void)
{
  setDefaultOsMemIntfForUnittests();
  setDefaultListIntfForUnittests();
}

void test_list_teardown(void)
{
  resetDefaultListIntfForUnittests();
  resetDefaultOsMemIntfForUnittests();
}
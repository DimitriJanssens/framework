#include "osutils.h"

#ifdef UNITTESTS
void setDefaultOsUtilsIntfForUnittests(void)
{
  OsUtilsIntf_t * intf = getOsUtilsIntf();
  intf->sleep_sec = osutils_sleep_sec;
  intf->sleep_usec = osutils_sleep_usec;
  intf->sleep_nsec = osutils_sleep_nsec;
  intf->random = osutils_random;
  intf->time_now = osutils_time_now;
  intf->environ_get = osutils_environ_get;
}

void resetDefaultOsUtilsIntfForUnittests(void)
{
  OsUtilsIntf_t * intf = getOsUtilsIntf();
  intf->sleep_sec = NULL;
  intf->sleep_usec = NULL;
  intf->sleep_nsec = NULL;
  intf->random = NULL;
  intf->time_now = NULL;
  intf->environ_get = NULL;
}
#endif

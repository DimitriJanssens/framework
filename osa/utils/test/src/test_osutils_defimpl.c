#include "osutils.h"

#ifdef UNITTESTS
void setDefaultOsUtilsIntfForUnittests(void)
{
  OsUtilsIntf_t * intf = getOsUtilsIntf();
  intf->sleep_sec = osutils_sleep_sec;
  intf->sleep_usec = osutils_sleep_usec;
  intf->sleep_nsec = osutils_sleep_nsec;
  intf->random = osutils_random;
}

void resetDefaultOsUtilsIntfForUnittests(void)
{
  OsUtilsIntf_t * intf = getOsUtilsIntf();
  intf->sleep_sec = NULL;
  intf->sleep_usec = NULL;
  intf->sleep_nsec = NULL;
  intf->random = NULL;
}
#endif

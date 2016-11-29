#include "osstring.h"

#ifdef UNITTESTS
void setDefaultOsStringIntfForUnittests(void)
{
  OsStringIntf_t * intf = getOsStringIntf();
  intf->string_write = osstring_write;
  intf->string_scan = osstring_scan;
  intf->string_length = osstring_length;
}

void resetDefaultOsStringIntfForUnittests(void)
{
  OsStringIntf_t * intf = getOsStringIntf();
  intf->string_write = NULL;
  intf->string_scan = NULL;
  intf->string_length = NULL;
}
#endif

#include "osfile.h"

#ifdef UNITTESTS
void setDefaultOsFileIntfForUnittests(void)
{
  OsFileIntf_t * intf = getOsFileIntf();
  intf->file_open = osfile_open;
  intf->file_size = osfile_size;
  intf->file_read = osfile_read;
  intf->file_write = osfile_write;
  intf->file_close = osfile_close;
}

void resetDefaultOsFileIntfForUnittests(void)
{
  OsFileIntf_t * intf = getOsFileIntf();
  intf->file_open = NULL;
  intf->file_size = NULL;
  intf->file_read = NULL;
  intf->file_write = NULL;
  intf->file_close = NULL;
}
#endif

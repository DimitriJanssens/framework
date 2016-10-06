#include "osepoll.h"

#ifdef UNITTESTS
void setDefaultOsEpollIntfForUnittests(void)
{
  OsEpollIntf_t * intf = getOsEpollIntf();
  intf->create = osepoll_create;
  intf->ctl_add = osepoll_register;
  intf->wait = osepoll_wait;
  intf->ctl_del = osepoll_unregister;
  intf->close = osepoll_close;
}

void resetDefaultOsEpollIntfForUnittests(void)
{
  OsEpollIntf_t * intf = getOsEpollIntf();
  intf->create = NULL;
  intf->ctl_add = NULL;
  intf->wait = NULL;
  intf->ctl_del = NULL;
  intf->close = NULL;
}
#endif

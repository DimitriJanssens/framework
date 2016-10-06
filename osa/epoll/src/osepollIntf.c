#include <osa/osepollIntf.h>

#include "osepoll.h"

static OsEpollIntf_t intf =
{
  #ifndef UNITTESTS
  .create = osepoll_create,
  .ctl_add = osepoll_register,
  .wait = osepoll_wait,
  .ctl_del = osepoll_unregister,
  .close = osepoll_close,
  #else
  .create = NULL,
  .ctl_add = NULL,
  .wait = NULL,
  .ctl_del = NULL,
  .close = NULL,
  #endif
};

OsEpollIntf_t * getOsEpollIntf(void)
{
  return &intf;
}

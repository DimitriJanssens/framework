#include "osreactor.h"

#ifdef UNITTESTS
void setDefaultOsReactorIntfForUnittests(void)
{
  OsReactorIntf_t * intf = getOsReactorIntf();

  intf->reactor_create = osreactor_reactor_create;
  intf->reactor_channel_register = osreactor_reactor_channel_register;
  intf->reactor_channel_unregister = osreactor_reactor_channel_unregister;
  intf->reactor_destroy = osreactor_reactor_destroy;

  intf->channel_create = osreactor_channel_create;
  intf->channel_get_socket = osreactor_channel_get_socket;
  intf->channel_get_userdata = osreactor_channel_get_userdata;
  intf->channel_destroy = osreactor_channel_destroy;
}

void resetDefaultOsReactorIntfForUnittests(void)
{
  OsReactorIntf_t * intf = getOsReactorIntf();

  intf->reactor_create = NULL;
  intf->reactor_channel_register = NULL;
  intf->reactor_channel_unregister = NULL;
  intf->reactor_destroy = NULL;

  intf->channel_create = NULL;
  intf->channel_get_socket = NULL;
  intf->channel_get_userdata = NULL;
  intf->channel_destroy = NULL;
}
#endif

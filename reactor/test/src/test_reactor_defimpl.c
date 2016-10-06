#include "reactor.h"

#ifdef UNITTESTS
void setDefaultReactorIntfForUnittests(void)
{
  ReactorIntf_t * intf = getReactorIntf();

  intf->reactor_create = reactor_reactor_create;
  intf->reactor_channel_register = reactor_reactor_channel_register;
  intf->reactor_channel_unregister = reactor_reactor_channel_unregister;
  intf->reactor_destroy = reactor_reactor_destroy;

  intf->channel_create = reactor_channel_create;
  intf->channel_get_socket = reactor_channel_get_socket;
  intf->channel_get_userdata = reactor_channel_get_userdata;
  intf->channel_destroy = reactor_channel_destroy;
}

void resetDefaultReactorIntfForUnittests(void)
{
  ReactorIntf_t * intf = getReactorIntf();

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

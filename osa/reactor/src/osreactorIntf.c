#include <osa/osreactorIntf.h>

#include "osreactor.h"

static OsReactorIntf_t intf = 
{
  #ifndef UNITTESTS
  .reactor_create = osreactor_reactor_create,
  .reactor_channel_register = osreactor_reactor_channel_register,
  .reactor_channel_unregister = osreactor_reactor_channel_unregister,
  .reactor_destroy = osreactor_reactor_destroy,

  .channel_create = osreactor_channel_create,
  .channel_get_socket = osreactor_channel_get_socket,
  .channel_get_userdata = osreactor_channel_get_userdata,
  .channel_destroy = osreactor_channel_destroy,
  #else
  .reactor_create = NULL,
  .reactor_channel_register = NULL,
  .reactor_channel_unregister = NULL,
  .reactor_destroy = NULL,

  .channel_create = NULL,
  .channel_get_socket = NULL,
  .channel_get_userdata = NULL,
  .channel_destroy = NULL,
  #endif
};

OsReactorIntf_t * getOsReactorIntf(void)
{
  return &intf;
}

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
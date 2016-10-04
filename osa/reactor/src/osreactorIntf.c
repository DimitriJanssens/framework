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

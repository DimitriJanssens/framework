#include <reactor/reactorIntf.h>

#include "reactor.h"

static ReactorIntf_t intf =
{
  #ifndef UNITTESTS
  .reactor_create = reactor_reactor_create,
  .reactor_channel_register = reactor_reactor_channel_register,
  .reactor_channel_unregister = reactor_reactor_channel_unregister,
  .reactor_destroy = reactor_reactor_destroy,

  .channel_create = reactor_channel_create,
  .channel_get_socket = reactor_channel_get_socket,
  .channel_get_userdata = reactor_channel_get_userdata,
  .channel_destroy = reactor_channel_destroy,
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

ReactorIntf_t * getReactorIntf(void)
{
  return &intf;
}

#include <protocols/canIntf.h>

#include "can_socket.h"

static CanIntf_t intf =
{
  .socket_create = can_socket_create,
  .socket_write = can_socket_write,
  .socket_read = can_socket_read,
  .socket_destroy = can_socket_destroy,
};

CanIntf_t * getCanIntf(void)
{
  return &intf;
}
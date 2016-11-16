#include <protocols/tcpIntf.h>

#include "tcp_socket.h"

static TcpIntf_t intf =
{
  #ifndef UNITTESTS
  .socket_create_connect = tcp_socket_create_connect,
  .socket_write = tcp_socket_write,
  .socket_read = tcp_socket_read,
  .socket_destroy = tcp_socket_destroy,
  #else
  .socket_create_connect = NULL,
  .socket_write = NULL,
  .socket_read = NULL,
  .socket_destroy = NULL,
  #endif
};

TcpIntf_t * getTcpIntf(void)
{
  return &intf;
}

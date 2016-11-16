#include <osa/osnetIntf.h>

#include "osnet.h"

static OsNetIntf_t intf =
{
  #ifndef UNITTESTS
  .socket_index_for_interface = osnet_socket_index_for_interface,
  .socket_create = osnet_socket_create,
  .socket_fd = osnet_socket_fd,
  .socket_nonblocking = osnet_socket_nonblocking,
  .socket_bind = osnet_socket_bind,
  .socket_connect = osnet_socket_connect,
  .socket_listen = osnet_socket_listen,
  .socket_accept = osnet_socket_accept,
  .socket_send = osnet_socket_send,
  .socket_sendto = osnet_socket_sendto,
  .socket_recv = osnet_socket_recv,
  .socket_recvfrom = osnet_socket_recvfrom,
  .socket_destroy = osnet_socket_destroy,

  .host_to_network_long = osnet_htonl,
  .host_to_network_short = osnet_htons,
  .network_to_host_long = osnet_ntohl,
  .network_to_host_short = osnet_ntohs,
  #else
  .socket_index_for_interface = NULL,
  .socket_create = NULL,
  .socket_fd = NULL,
  .socket_nonblocking = NULL,
  .socket_bind = NULL,
  .socket_connect = NULL,
  .socket_listen = NULL,
  .socket_accept = NULL,
  .socket_send = NULL,
  .socket_sendto = NULL,
  .socket_recv = NULL,
  .socket_recvfrom = NULL,
  .socket_destroy = NULL,

  .host_to_network_long = NULL,
  .host_to_network_short = NULL,
  .network_to_host_long = NULL,
  .network_to_host_short = NULL,
  #endif
};

OsNetIntf_t * getOsNetIntf(void)
{
  return &intf;
}

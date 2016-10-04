#include <osa/osnetIntf.h>

#include "osnet.h"

static OsNetIntf_t intf =
{
  #ifndef UNITTESTS
  .socket_index_for_interface = osnet_socket_index_for_interface,
  .socket_create = osnet_socket_create,
  .socket_fd = osnet_socket_fd,
  .socket_bind = osnet_socket_bind,
  .socket_send = osnet_socket_send,
  .socket_sendto = osnet_socket_sendto,
  .socket_recv = osnet_socket_recv,
  .socket_recvfrom = osnet_socket_recvfrom,
  .socket_destroy = osnet_socket_destroy,

  .htonl = osnet_htonl,
  .htons = osnet_htons,
  .ntohl = osnet_ntohl,
  .ntohs = osnet_ntohs,
  #else
  .socket_index_for_interface = NULL,
  .socket_create = NULL,
  .socket_fd = NULL,
  .socket_bind = NULL,
  .socket_send = NULL,
  .socket_sendto = NULL,
  .socket_recv = NULL,
  .socket_recvfrom = NULL,
  .socket_destroy = NULL,

  .htonl = NULL,
  .htons = NULL,
  .ntohl = NULL,
  .ntohs = NULL,
  #endif
};

OsNetIntf_t * getOsNetIntf(void)
{
  return &intf;
}

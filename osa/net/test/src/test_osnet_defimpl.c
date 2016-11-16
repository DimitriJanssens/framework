#include "osnet.h"

#ifdef UNITTESTS
void setDefaultOsNetIntfForUnittests(void)
{
  OsNetIntf_t * intf = getOsNetIntf();

  intf->socket_index_for_interface = osnet_socket_index_for_interface;
  intf->socket_create = osnet_socket_create;
  intf->socket_fd = osnet_socket_fd;
  intf->socket_nonblocking = osnet_socket_nonblocking;
  intf->socket_bind = osnet_socket_bind;
  intf->socket_connect = osnet_socket_connect;
  intf->socket_listen = osnet_socket_listen;
  intf->socket_accept = osnet_socket_accept;
  intf->socket_send = osnet_socket_send;
  intf->socket_sendto = osnet_socket_sendto;
  intf->socket_recv = osnet_socket_recv;
  intf->socket_recvfrom = osnet_socket_recvfrom;
  intf->socket_destroy = osnet_socket_destroy;

  intf->host_to_network_long = osnet_htonl;
  intf->host_to_network_short = osnet_htons;
  intf->network_to_host_long = osnet_ntohl;
  intf->network_to_host_short = osnet_ntohs;
}

void resetDefaultOsNetIntfForUnittests(void)
{
  OsNetIntf_t * intf = getOsNetIntf();

  intf->socket_index_for_interface = NULL;
  intf->socket_create = NULL;
  intf->socket_fd = NULL;
  intf->socket_nonblocking = NULL;
  intf->socket_bind = NULL;
  intf->socket_connect = NULL;
  intf->socket_listen = NULL;
  intf->socket_accept = NULL;
  intf->socket_send = NULL;
  intf->socket_sendto = NULL;
  intf->socket_recv = NULL;
  intf->socket_recvfrom = NULL;
  intf->socket_destroy = NULL;

  intf->host_to_network_long = NULL;
  intf->host_to_network_short = NULL;
  intf->network_to_host_long = NULL;
  intf->network_to_host_short = NULL;
}
#endif

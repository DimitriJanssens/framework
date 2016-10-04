#include "osnet.h"

#ifdef UNITTESTS
void setDefaultOsNetIntfForUnittests(void)
{
  OsNetIntf_t * intf = getOsNetIntf();

  intf->socket_index_for_interface = osnet_socket_index_for_interface;
  intf->socket_create = osnet_socket_create;
  intf->socket_fd = osnet_socket_fd;
  intf->socket_bind = osnet_socket_bind;
  intf->socket_send = osnet_socket_send;
  intf->socket_sendto = osnet_socket_sendto;
  intf->socket_recv = osnet_socket_recv;
  intf->socket_recvfrom = osnet_socket_recvfrom;
  intf->socket_destroy = osnet_socket_destroy;

  intf->htonl = osnet_htonl;
  intf->htons = osnet_htons;
  intf->ntohl = osnet_ntohl;
  intf->ntohs = osnet_ntohs;
}
void resetDefaultOsNetIntfForUnittests(void)
{
  OsNetIntf_t * intf = getOsNetIntf();

  intf->socket_index_for_interface = NULL;
  intf->socket_create = NULL;
  intf->socket_fd = NULL;
  intf->socket_bind = NULL;
  intf->socket_send = NULL;
  intf->socket_sendto = NULL;
  intf->socket_recv = NULL;
  intf->socket_recvfrom = NULL;
  intf->socket_destroy = NULL;

  intf->htonl = NULL;
  intf->htons = NULL;
  intf->ntohl = NULL;
  intf->ntohs = NULL;
}
#endif

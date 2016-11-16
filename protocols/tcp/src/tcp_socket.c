#include "tcp_socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

Status_e tcp_socket_create_listen(OsNetSocket_t ** sckt, const TcpSocketIpv4Address_t * const address, uint16_t maxpendingconnections)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (address != NULL))
  {
    const OsNetIntf_t * const neti = getOsNetIntf();
    if(neti->socket_create(OSNETSOCKETTYPE_TCP, sckt) == STATUS_SUCCESS)
    {
      struct sockaddr_in osaddr;
      osaddr.sin_family = AF_INET;
      osaddr.sin_port = neti->host_to_network_short(address->port);
      osaddr.sin_addr.s_addr = neti->host_to_network_long(address->address);
      if(neti->socket_bind(*sckt, &osaddr, sizeof(osaddr)) == STATUS_SUCCESS)
      {
        if(neti->socket_listen(*sckt, maxpendingconnections) == STATUS_SUCCESS)
        {
          if(neti->socket_nonblocking(*sckt, BOOLEAN_TRUE) == STATUS_SUCCESS)
          {
            rc = STATUS_SUCCESS;
          }
        }
      }

      if(rc != STATUS_SUCCESS)
      {
        (void) neti->socket_destroy(*sckt);
      }
    }
  }

  return rc;
}

Status_e tcp_socket_create_connect(OsNetSocket_t ** sckt, const TcpSocketIpv4Address_t * const address)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (address != NULL))
  {
    const OsNetIntf_t * const neti = getOsNetIntf();
    if(neti->socket_create(OSNETSOCKETTYPE_TCP, sckt) == STATUS_SUCCESS)
    {
      struct sockaddr_in osaddr;
      osaddr.sin_family = AF_INET;
      osaddr.sin_port = neti->host_to_network_short(address->port);
      osaddr.sin_addr.s_addr = neti->host_to_network_long(address->address);
      if(neti->socket_connect(*sckt, &osaddr, sizeof(osaddr)) == STATUS_SUCCESS)
      {
        rc = STATUS_SUCCESS;
      }
      else
      {
        (void) neti->socket_destroy(*sckt);
      }
    }
  }

  return rc;
}

Status_e tcp_socket_write(const OsNetSocket_t * sckt, const uint8_t * const data, size_t size, size_t * const txbytes)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (data != NULL) && (txbytes != NULL))
  {
    const OsNetIntf_t * const ni = getOsNetIntf();
    *txbytes = size;
    if(ni->socket_send(sckt, data, txbytes, 0) == STATUS_SUCCESS)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e tcp_socket_read(const OsNetSocket_t * sckt, uint8_t * const data, size_t size, size_t * const rxbytes)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (data != NULL) && (rxbytes != NULL))
  {
    const OsNetIntf_t * const ni = getOsNetIntf();
    *rxbytes = size;
    if(ni->socket_recv(sckt, data, rxbytes, MSG_DONTWAIT) == STATUS_SUCCESS)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e tcp_socket_destroy(OsNetSocket_t * sckt)
{
  Status_e rc = STATUS_FAILURE;

  if(sckt != NULL)
  {
    rc = getOsNetIntf()->socket_destroy(sckt);
  }

  return rc;
}

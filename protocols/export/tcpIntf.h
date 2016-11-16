#ifndef TCPINTF_H
#define TCPINTF_H

#include <common/commontypes.h>

#include <osa/osnetIntf.h>
#include <reactor/reactorIntf.h>

typedef struct TcpServer TcpServer_t;

#define TCPSOCKETIPV4ADDRESS(a,b,c,d) ((uint32_t)((a<<24) | (b<<16) | (c<<8) | (d<<0)))

typedef struct
{
  uint32_t address;
  uint16_t port;
} TcpSocketIpv4Address_t;

typedef struct
{
  Status_e (*socket_create_connect)(OsNetSocket_t ** sckt, const TcpSocketIpv4Address_t * const address);
  Status_e (*socket_write)(const OsNetSocket_t * sckt, const uint8_t * const data, size_t size, size_t * const txbytes);
  Status_e (*socket_read)(const OsNetSocket_t * sckt, uint8_t * const data, size_t size, size_t * const rxbytes);
  Status_e (*socket_destroy)(OsNetSocket_t * sckt);
} TcpIntf_t;

TcpIntf_t * getTcpIntf(void);

#endif

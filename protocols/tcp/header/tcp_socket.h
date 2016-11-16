#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <protocols/tcpIntf.h>

Status_e tcp_socket_create_listen(OsNetSocket_t ** sckt, const TcpSocketIpv4Address_t * const address, uint16_t maxpendingconnections);
Status_e tcp_socket_create_connect(OsNetSocket_t ** sckt, const TcpSocketIpv4Address_t * const address);
Status_e tcp_socket_write(const OsNetSocket_t * sckt, const uint8_t * const data, size_t size, size_t * const txbytes);
Status_e tcp_socket_read(const OsNetSocket_t * sckt, uint8_t * const data, size_t size, size_t * const rxbytes);
Status_e tcp_socket_destroy(OsNetSocket_t * sckt);

#endif

#ifndef OSNET_H
#define OSNET_H

#include <osa/osnetIntf.h>

Status_e osnet_socket_index_for_interface(const OsNetSocket_t * sckt, const char_t * const ifname, int32_t * const ifindex);
Status_e osnet_socket_create(OsNetSocketType_e type, OsNetSocket_t ** sckt);
int32_t osnet_socket_fd(const OsNetSocket_t * const sckt);
Status_e osnet_socket_bind(const OsNetSocket_t * sckt, const void * const addr, size_t size);
Status_e osnet_socket_send(const OsNetSocket_t * sckt, const void * const data, size_t * data_size, int32_t flags);
Status_e osnet_socket_sendto(const OsNetSocket_t * sckt, const void * const data, size_t * data_size, int32_t flags, const void * const dest_addr, size_t dest_addr_size);
Status_e osnet_socket_recv(const OsNetSocket_t * sckt, void * const data, size_t * data_size, int32_t flags);
Status_e osnet_socket_recvfrom(const OsNetSocket_t * sckt, void * const data, size_t * data_size, int32_t flags, void * const src_addr, size_t * const src_addr_size);
Status_e osnet_socket_destroy(OsNetSocket_t * sckt);

uint32_t osnet_htonl(uint32_t hostlong);
uint16_t osnet_htons(uint16_t hostshort);
uint32_t osnet_ntohl(uint32_t netlong);
uint16_t osnet_ntohs(uint16_t netshort);

#endif

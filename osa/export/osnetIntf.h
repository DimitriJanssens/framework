#ifndef OSNETINTF_H
#define OSNETINTF_H

#include <common/commontypes.h>

typedef struct OsNetSocket OsNetSocket_t;
typedef enum
{
  OSNETSOCKETTYPE_UNKNOWN = 0,
  OSNETSOCKETTYPE_UDP,
  OSNETSOCKETTYPE_TCP,
  OSNETSOCKETTYPE_CAN,
} OsNetSocketType_e;

typedef struct
{
  Status_e (*socket_index_for_interface)(const OsNetSocket_t * sckt, const char_t * const ifname, int32_t * const ifindex);
  Status_e (*socket_create)(OsNetSocketType_e type, OsNetSocket_t ** sckt);
  int32_t (*socket_fd)(const OsNetSocket_t * const sckt);
  Status_e (*socket_nonblocking)(const OsNetSocket_t * const sckt, Boolean_e on);
  Status_e (*socket_bind)(const OsNetSocket_t * sckt, const void * const addr, size_t addr_size);
  Status_e (*socket_connect)(const OsNetSocket_t * sckt, const void * const addr, size_t addr_size);
  Status_e (*socket_listen)(const OsNetSocket_t * sckt, uint16_t maxpendingconnections);
  Status_e (*socket_accept)(const OsNetSocket_t * sckt, OsNetSocket_t ** newsckt, void * const addr, size_t * const addr_size);
  Status_e (*socket_send)(const OsNetSocket_t * sckt, const void * const data, size_t * const data_size, int32_t flags);
  Status_e (*socket_sendto)(const OsNetSocket_t * sckt, const void * const data, size_t * const data_size, int32_t flags, const void * const dest_addr, size_t dest_addr_size);
  Status_e (*socket_recv)(const OsNetSocket_t * sckt, void * const data, size_t * const data_size, int32_t flags);
  Status_e (*socket_recvfrom)(const OsNetSocket_t * sckt, void * const data, size_t * const data_size, int32_t flags, void * const src_addr, size_t * const src_addr_size);
  Status_e (*socket_destroy)(OsNetSocket_t * sckt);

  uint32_t (*host_to_network_long)(uint32_t hostlong);
  uint16_t (*host_to_network_short)(uint16_t hostshort);
  uint32_t (*network_to_host_long)(uint32_t netlong);
  uint16_t (*network_to_host_short)(uint16_t netshort);
} OsNetIntf_t;

OsNetIntf_t * getOsNetIntf(void);

#ifdef UNITTESTS
void setDefaultOsNetIntfForUnittests(void);
void resetDefaultOsNetIntfForUnittests(void);
#endif

#endif

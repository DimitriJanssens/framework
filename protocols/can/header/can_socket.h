#ifndef CAN_SOCKET_H
#define CAN_SOCKET_H

#include <protocols/canIntf.h>

Status_e can_socket_create(OsNetSocket_t ** sckt, const char_t * const ifname);
Status_e can_socket_write(const OsNetSocket_t * sckt, const CanFrame_t * const frame);
Status_e can_socket_read(const OsNetSocket_t * sckt, CanFrame_t * const frame);
Status_e can_socket_destroy(OsNetSocket_t * sckt);

#endif
#ifndef CANINTF_H
#define CANINTF_H

#include <common/commontypes.h>

#include <osa/osnetIntf.h>

/* special address description flags for the CAN_ID */
#define CAN_FRAMEFORMAT_FLAG_EFF 0x80000000U /* EFF/SFF is set in the MSB */
#define CAN_FRAMEFORMAT_FLAG_RTR 0x40000000U /* remote transmission request */
#define CAN_FRAMEFORMAT_FLAG_ERR 0x20000000U /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_FRAMEFORMAT_MASK_SFF 0x000007FFU /* standard frame format (SFF) */
#define CAN_FRAMEFORMAT_MASK_EFF 0x1FFFFFFFU /* extended frame format (EFF) */
#define CAN_FRAMEFORMAT_MASK_ERR 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

#define CAN_FRAMEFORMAT_DATA_SIZE_MAX  8
typedef struct
{
  /* can id + flags */
  uint32_t canid;
  uint8_t data[CAN_FRAMEFORMAT_DATA_SIZE_MAX];
  uint8_t size;
} CanFrame_t;

typedef struct
{
  Status_e (*socket_create)(OsNetSocket_t ** sckt, const char_t * const ifname);
  Status_e (*socket_write)(const OsNetSocket_t * sckt, const CanFrame_t * const frame);
  Status_e (*socket_read)(const OsNetSocket_t * sckt, CanFrame_t * const frame);
  Status_e (*socket_destroy)(OsNetSocket_t * sckt);
} CanIntf_t;

CanIntf_t * getCanIntf(void);

#endif

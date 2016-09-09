#include "can_socket.h"

#include <linux/can.h>
#include <sys/socket.h>

#include <osa/osmemIntf.h>

Status_e can_socket_create(OsNetSocket_t ** sckt, const char_t * const ifname)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (ifname != NULL))
  {
    const OsNetIntf_t * const neti = getOsNetIntf();
    if(neti->socket_create(OSNETSOCKETTYPE_CAN, sckt) == STATUS_SUCCESS)
    {
      int32_t ifindex;
      if(neti->socket_index_for_interface(*sckt, ifname, &ifindex) == STATUS_SUCCESS)
      {
        struct sockaddr_can can_addr;
        can_addr.can_family  = AF_CAN;
        can_addr.can_ifindex = ifindex;

        if(neti->socket_bind(*sckt, &can_addr, sizeof(can_addr)) == STATUS_SUCCESS)
        {
          rc = STATUS_SUCCESS;
        }
        else
        {
          (void) neti->socket_destroy(*sckt);
        }
      }
    }
  }

  return rc;
}

Status_e can_socket_write(const OsNetSocket_t * sckt, const CanFrame_t * const frame)
{
  Status_e rc = STATUS_SUCCESS;

  if((sckt != NULL) && (frame != NULL))
  {
    struct can_frame can_frame;
    can_frame.can_id = frame->canid;
    can_frame.can_dlc = frame->size;
    if(getOsMemIntf()->memcpy(can_frame.data, frame->data, ARRAY_SIZE(can_frame.data)) == STATUS_SUCCESS)
    {
      const OsNetIntf_t * const neti = getOsNetIntf();
      size_t can_frame_size = sizeof(can_frame);
      rc = neti->socket_send(sckt, &can_frame, &can_frame_size, 0);
    }
  }

  return rc;
}

Status_e can_socket_read(const OsNetSocket_t * sckt, CanFrame_t * const frame)
{
  Status_e rc = STATUS_SUCCESS;

  if((sckt != NULL) && (frame != NULL))
  {
    const OsNetIntf_t * const neti = getOsNetIntf();
    struct can_frame can_frame;
    size_t can_frame_size = sizeof(can_frame);
    if(neti->socket_recv(sckt, &can_frame, &can_frame_size, 0) == STATUS_SUCCESS)
    {
      if(getOsMemIntf()->memcpy(frame->data, can_frame.data, ARRAY_SIZE(frame->data)) == STATUS_SUCCESS)
      {
        frame->canid = can_frame.can_id;
        frame->size = can_frame.can_dlc;

        rc = STATUS_SUCCESS;
      }
    }
  }

  return rc;
}

Status_e can_socket_destroy(OsNetSocket_t * sckt)
{
  Status_e rc = STATUS_FAILURE;

  if(sckt != NULL)
  {
    rc = getOsNetIntf()->socket_destroy(sckt);
  }

  return rc;
}

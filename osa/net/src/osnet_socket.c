#include "osnet.h"

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <osa/osmemIntf.h>
#include <logging/logging.h>

struct OsNetSocket
{
  int32_t fd;
};

Status_e osnet_socket_index_for_interface(const OsNetSocket_t * sckt, const char_t * const ifname, int32_t * const ifindex)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (ifname != NULL) && (ifindex != NULL))
  {
    const OsMemIntf_t * const memi = getOsMemIntf();

    struct ifreq _ifreq;
    if(memi->memcpy(_ifreq.ifr_name, ifname, IFNAMSIZ) == STATUS_SUCCESS)
    {
      if(ioctl(sckt->fd, SIOCGIFINDEX, &_ifreq) > -1)
      {
        *ifindex = _ifreq.ifr_ifindex;
        rc = STATUS_SUCCESS;
      }
    }
  }

  return rc;
}

Status_e osnet_socket_create(OsNetSocketType_e type, OsNetSocket_t ** sckt)
{
  Status_e rc = STATUS_FAILURE;

  if((type != OSNETSOCKETTYPE_UNKNOWN) && (sckt != NULL))
  {
    const OsMemIntf_t * const memi = getOsMemIntf();

    *sckt = (struct OsNetSocket *) memi->malloc(sizeof(struct OsNetSocket));
    if(*sckt != NULL)
    {
      int s = -1;

      if(type == OSNETSOCKETTYPE_UDP)
      {
        s = socket(AF_INET, SOCK_DGRAM, 0);
      }
      else if(type == OSNETSOCKETTYPE_CAN)
      {
        s = socket(AF_CAN, SOCK_RAW, CAN_RAW);
      }

      if(s > -1)
      {
        (*sckt)->fd = s;
        rc = STATUS_SUCCESS;
      }
      else
      {
        memi->free(*sckt);
      }
    }
  }

  return rc;
}

int32_t osnet_socket_fd(const OsNetSocket_t * const sckt)
{
  int32_t rc = -1;

  if(sckt != NULL)
  {
    rc = sckt->fd;
  }

  return rc;
}

Status_e osnet_socket_bind(const OsNetSocket_t * sckt, const void * const addr, size_t addr_size)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (addr != NULL) && (addr_size > 0))
  {
    if(bind(sckt->fd, (const struct sockaddr *) addr, (socklen_t) addr_size) > -1)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osnet_socket_send(const OsNetSocket_t * sckt, const void * const data, size_t * data_size, int32_t flags)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (data != NULL) && (data_size != 0))
  {
    rc = getOsNetIntf()->socket_sendto(sckt, data, data_size, flags, NULL, 0);
  }

  return rc;
}

Status_e osnet_socket_sendto(const OsNetSocket_t * sckt, const void * const data, size_t * data_size, int32_t flags, const void * const dest_addr, size_t dest_addr_size)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (data != NULL) && (data_size != 0))
  {
    ssize_t nbytes = -1;

    if(dest_addr == NULL)
    {
      nbytes = sendto(sckt->fd, data, *data_size, flags, NULL, 0);
    }
    else
    {
      nbytes = sendto(sckt->fd, data, *data_size, flags, (const struct sockaddr *) dest_addr, dest_addr_size);
    }

    if(nbytes > -1)
    {
      *data_size = (size_t) nbytes;
      rc = STATUS_SUCCESS;
    }
    else
    {
      const char_t * error = strerror(errno);
      if((errno == EAGAIN) || (errno == EWOULDBLOCK))
      {
        *data_size = 0;

        DEBUG("Socket sendto: %s\n", error);
        rc = STATUS_SUCCESS;
      }
      else
      {
        ERROR("Socket sendto: %s\n", error);
      }
    }
  }

  return rc;
}

Status_e osnet_socket_recv(const OsNetSocket_t * sckt, void * const data, size_t * data_size, int32_t flags)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (data != NULL) && (data_size != 0))
  {
    rc = getOsNetIntf()->socket_recvfrom(sckt, data, data_size, flags, NULL, NULL);
  }

  return rc;
}

Status_e osnet_socket_recvfrom(const OsNetSocket_t * sckt, void * const data, size_t * data_size, int32_t flags, void * const src_addr, size_t * const src_addr_size)
{
  Status_e rc = STATUS_FAILURE;

  if((sckt != NULL) && (data != NULL) && (data_size != 0))
  {
    ssize_t nbytes = -1;

    if((src_addr == NULL) && (src_addr_size == NULL))
    {
      nbytes = recvfrom(sckt->fd, data, *data_size, flags, NULL, NULL);
    }
    else
    {
      nbytes = recvfrom(sckt->fd, data, *data_size, flags, (struct sockaddr *)src_addr, src_addr_size);
    }

    if(nbytes > -1)
    {
      *data_size = (size_t) nbytes;
      rc = STATUS_SUCCESS;
    }
    else
    {
      const char_t * error = strerror(errno);
      if((errno == EAGAIN) || (errno == EWOULDBLOCK))
      {
        *data_size = 0;

        DEBUG("Socket recvfrom: %s\n", error);
        rc = STATUS_SUCCESS;
      }
      else
      {
        ERROR("Socket recvfrom: %s\n", error);
      }
    }
  }

  return rc;
}

Status_e osnet_socket_destroy(OsNetSocket_t * socket)
{
  Status_e rc = STATUS_FAILURE;

  if(socket != NULL)
  {
    if(close(socket->fd) == 0)
    {
      socket->fd = -1;
      getOsMemIntf()->free(socket);
      socket = NULL;
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

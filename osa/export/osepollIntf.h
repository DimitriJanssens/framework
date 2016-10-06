#ifndef OSEPOLLINTF_H
#define OSEPOLLINTF_H

#include <common/commontypes.h>

#define OSEPOLLEVENT_UNKNOWN (1u << 0)
#define OSEPOLLEVENT_TIMEOUT (1u << 1)
#define OSEPOLLEVENT_IN (1u << 2)
#define OSEPOLLEVENT_OUT (1u << 3)
#define OSEPOLLEVENT_RDHUP (1u << 4)
#define OSEPOLLEVENT_PRI (1u << 5)
#define OSEPOLLEVENT_ERR (1u << 6)
#define OSEPOLLEVENT_HUP (1u << 7)
#define OSEPOLLEVENT_ET (1u << 8)

typedef struct
{
  uint32_t events;
  void * data;
} OsEpollEvent_t;

typedef struct
{
  Status_e (*create)(int32_t * epollfd);
  Status_e (*ctl_add)(int32_t epollfd, int32_t fd, const OsEpollEvent_t * const event);
  Status_e (*wait)(int32_t epollfd, OsEpollEvent_t * const event);
  Status_e (*ctl_del)(int32_t epollfd, int32_t fd);
  Status_e (*close)(int32_t epollfd);
} OsEpollIntf_t;

OsEpollIntf_t * getOsEpollIntf(void);

#ifdef UNITTESTS
void setDefaultOsEpollIntfForUnittests(void);
void resetDefaultOsEpollIntfForUnittests(void);
#endif

#endif

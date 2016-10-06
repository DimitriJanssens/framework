#include "osepoll.h"

#include <sys/epoll.h>

int32_t osepoll_events_to_os(int32_t events)
{
  int32_t rc = 0;

  if(events & OSEPOLLEVENT_IN)
    rc |= EPOLLIN;
  if(events & OSEPOLLEVENT_OUT)
    rc |= EPOLLOUT;
  if(events & OSEPOLLEVENT_RDHUP)
    rc |= EPOLLRDHUP;
  if(events & OSEPOLLEVENT_PRI)
    rc |= EPOLLPRI;
  if(events & OSEPOLLEVENT_ERR)
    rc |= EPOLLERR;
  if(events & OSEPOLLEVENT_HUP)
    rc |= EPOLLHUP;
  if(events & OSEPOLLEVENT_ET)
    rc |= EPOLLET;

  return rc;
}

int32_t osepoll_events_from_os(int32_t events)
{
  int32_t rc = 0;

  if(events & EPOLLIN)
    rc |= OSEPOLLEVENT_IN;
  if(events & EPOLLOUT)
    rc |= OSEPOLLEVENT_OUT;
  if(events & EPOLLRDHUP)
    rc |= OSEPOLLEVENT_RDHUP;
  if(events & EPOLLPRI)
    rc |= OSEPOLLEVENT_PRI;
  if(events & EPOLLERR)
    rc |= OSEPOLLEVENT_ERR;
  if(events & EPOLLHUP)
    rc |= OSEPOLLEVENT_HUP;
  if(events & EPOLLET)
    rc |= OSEPOLLEVENT_ET;

  return rc;
}

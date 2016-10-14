#include "osepoll.h"

#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <logging/logging.h>
#include <osa/osmemIntf.h>

Status_e osepoll_create(int32_t * epollfd)
{
  Status_e rc = STATUS_FAILURE;

  if(epollfd != NULL)
  {
    *epollfd = epoll_create1(0);
    if(*epollfd > -1)
    {
      rc = STATUS_SUCCESS;
    }
    else
    {
      const char_t * error = strerror(errno);
      ERROR("epoll_create: %s\n", error);
    }
  }

  return rc;
}

Status_e osepoll_register(int32_t epollfd, int32_t fd, const OsEpollEvent_t * const event)
{
  Status_e rc = STATUS_FAILURE;

  if(event != NULL)
  {
    struct epoll_event epoll_event;
    (void) getOsMemIntf()->memset(&epoll_event, 0, sizeof(epoll_event));
    epoll_event.events = osepoll_events_to_os(event->events);
    epoll_event.data.ptr = event->data;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &epoll_event) == 0)
    {
      rc = STATUS_SUCCESS;
    }
    else
    {
      const char_t * error = strerror(errno);
      ERROR("epoll_ctl: %s\n", error);
    }
  }

  return rc;
}

Status_e osepoll_wait(int32_t epollfd, OsEpollEvent_t * const event)
{
  Status_e rc = STATUS_FAILURE;

  if(event != NULL)
  {
    struct epoll_event epoll_event;
    int32_t nfds = epoll_wait(epollfd, &epoll_event, 1, 100);
    if(nfds > -1)
    {
      if(nfds == 0)
      {
        event->events = OSEPOLLEVENT_TIMEOUT;
        event->data = NULL;
        rc = STATUS_SUCCESS;
      }
      else
      {
        event->events = osepoll_events_from_os(epoll_event.events);
        event->data = epoll_event.data.ptr;
        rc = STATUS_SUCCESS;
      }
    }
    else
    {
      const char_t * error = strerror(errno);
      ERROR("epoll_wait: %s\n", error);
    }
  }

  return rc;
}

Status_e osepoll_unregister(int32_t epollfd, int32_t fd)
{
  Status_e rc = STATUS_FAILURE;

  struct epoll_event epoll_event;
  if(epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &epoll_event) == 0)
  {
    rc = STATUS_SUCCESS;
  }
  else
  {
    const char_t * error = strerror(errno);
    ERROR("epoll_ctl: %s\n", error);
  }

  return rc;
}

Status_e osepoll_close(int32_t epollfd)
{
  Status_e rc = STATUS_FAILURE;

  if(close(epollfd) == 0)
  {
    rc = STATUS_SUCCESS;
  }
  else
  {
    const char_t * error = strerror(errno);
    ERROR("epoll_close: %s\n", error);
  }

  return rc;
}

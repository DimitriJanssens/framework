#include "osreactor.h"

#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <logging/logging.h>
#include <osa/osmemIntf.h>
#include <osa/osthreadingIntf.h>
#include <collection/listIntf.h>

struct OsReactor
{
  enum OsReactorState
  {
    OSREACTORSTATE_UNKNOWN = 0,
    OSREACTORSTATE_START,
    OSREACTORSTATE_RUN,
    OSREACTORSTATE_STOP
  } state;
  List_t * channels;
  OsThread_t * thread;
  OsMutex_t * mutex;
  int32_t epollfd;
};

static void * localReactorThread(void * data);

Status_e osreactor_reactor_create(OsReactor_t ** reactor)
{
  Status_e rc = STATUS_FAILURE;

  if(reactor != NULL)
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    *reactor = (struct OsReactor *) memi->malloc(sizeof(struct OsReactor));
    if(*reactor != NULL)
    {
      Boolean_e allOk = BOOLEAN_TRUE;
      const ListIntf_t * const listi = getListIntf();
      if(listi->list_create(&(*reactor)->channels, (ListItemDestructor_t) osreactor_channel_destroy) == STATUS_SUCCESS)
      {
        const OsThreadingIntf_t * const thri = getOsThreadingIntf();
        if(thri->mutex_create(&(*reactor)->mutex) == STATUS_SUCCESS)
        {
          (*reactor)->epollfd = epoll_create1(0);
          if((*reactor)->epollfd > -1)
          {
            (*reactor)->state = OSREACTORSTATE_START;
            if(thri->thread_create(&(*reactor)->thread, localReactorThread, *reactor) == STATUS_SUCCESS)
            {            
              TRACE("OsReactor started\n");
              rc = STATUS_SUCCESS;
            }
            else
            {
              allOk = BOOLEAN_FALSE;
            }

            if(allOk == BOOLEAN_FALSE)
            {
              (void) close((*reactor)->epollfd);
            }
          }
          else
          {
            const char_t * error = strerror(errno);
            ERROR("epoll_create: %s\n", error);
            allOk = BOOLEAN_FALSE;
          }

          if(allOk == BOOLEAN_FALSE)
          {
            (void) thri->mutex_destroy((*reactor)->mutex);
          }
        }
        else
        {
          allOk = BOOLEAN_FALSE;
        }

        if(allOk == BOOLEAN_FALSE)
        {
          (void) listi->list_destroy((*reactor)->channels);
        }
      }
      else
      {
        allOk = BOOLEAN_FALSE;
      }

      if(allOk == BOOLEAN_FALSE)
      {
        memi->free(*reactor);
      }
    }
  }

  return rc;
}

Status_e osreactor_reactor_channel_register(OsReactor_t * reactor, OsReactorChannel_t * channel)
{
  Status_e rc = STATUS_FAILURE;

  if((reactor != NULL) && (channel != NULL))
  {
    const OsThreadingIntf_t * const thri = getOsThreadingIntf();
    if(thri->mutex_lock(reactor->mutex) == STATUS_SUCCESS)
    {
      const ListIntf_t * const listi = getListIntf();
      if(listi->item_append(reactor->channels, channel) == STATUS_SUCCESS)
      {
        int32_t fd = getOsNetIntf()->socket_fd(osreactor_channel_get_socket(channel));
        struct epoll_event epoll_event;
        (void) getOsMemIntf()->memset(&epoll_event, 0, sizeof(epoll_event));
        epoll_event.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP | EPOLLPRI | EPOLLERR | EPOLLHUP | EPOLLET;
        epoll_event.data.ptr = channel;
        if(epoll_ctl(reactor->epollfd, EPOLL_CTL_ADD, fd, &epoll_event) == 0)
        {
          rc = STATUS_SUCCESS;    
        }
        else
        {
          const char_t * error = strerror(errno);
          ERROR("epoll_ctl: %s\n", error);

          (void) listi->item_remove_index(reactor->channels, listi->list_size(reactor->channels) - 1);
        }
      }

      (void) thri->mutex_unlock(reactor->mutex);
    }
  }

  return rc;
}

Status_e osreactor_reactor_channel_unregister(OsReactor_t * reactor, OsReactorChannel_t * channel)
{
  Status_e rc = STATUS_FAILURE;

  if((reactor != NULL) && (channel != NULL))
  {
    const OsThreadingIntf_t * const thri = getOsThreadingIntf();
    if(thri->mutex_lock(reactor->mutex) == STATUS_SUCCESS)
    {
      const ListIntf_t * const listi = getListIntf();
      size_t size = listi->list_size(reactor->channels);
      for(size_t i = 0; i < size; i++)
      {
        OsReactorChannel_t * item = (OsReactorChannel_t *) listi->item_lookup_index(reactor->channels, i);
        if(channel == item)
        {
          int32_t fd = getOsNetIntf()->socket_fd(osreactor_channel_get_socket(channel));
          struct epoll_event epoll_event;
          if(epoll_ctl(reactor->epollfd, EPOLL_CTL_DEL, fd, &epoll_event) == 0)
          {
            rc = listi->item_remove_index(reactor->channels, i);
          }
          else
          {
            const char_t * error = strerror(errno);
            ERROR("epoll_ctl: %s\n", error);
          }
          break;
        }
      }

      (void) thri->mutex_unlock(reactor->mutex);
    }
  }

  return rc;
}

Status_e osreactor_reactor_destroy(OsReactor_t * reactor)
{
  Status_e rc = STATUS_FAILURE;

  if(reactor != NULL)
  {
    reactor->state = OSREACTORSTATE_STOP;

    const OsThreadingIntf_t * const thri = getOsThreadingIntf();
    if(thri->thread_destroy(reactor->thread) == STATUS_SUCCESS)
    {
      reactor->thread = NULL;

      if(thri->mutex_destroy(reactor->mutex) == STATUS_SUCCESS)
      {
        reactor->mutex = NULL;

        const ListIntf_t * const listi = getListIntf();
        if(listi->list_destroy(reactor->channels) == STATUS_SUCCESS)
        {
          reactor->channels = NULL;

          const OsMemIntf_t * const memi = getOsMemIntf();

          memi->free(reactor);
          
          rc = STATUS_SUCCESS;
        }
      }
    }
  }

  return rc;
}

static void * localReactorThread(void * data)
{
  OsReactor_t * reactor = (OsReactor_t *) data;

  if(reactor != NULL)
  {
    if(reactor->state == OSREACTORSTATE_START)
    {
      reactor->state = OSREACTORSTATE_RUN;
    }

    while(reactor->state == OSREACTORSTATE_RUN)
    {
      const OsThreadingIntf_t * const thri = getOsThreadingIntf();
     
      struct epoll_event epoll_event;
      int32_t nfds = epoll_wait(reactor->epollfd, &epoll_event, 1, 1);
      if(nfds >= -1)
      {
        if(nfds > 0)
        {
          if(thri->mutex_lock(reactor->mutex) == STATUS_SUCCESS)
          {
            const ListIntf_t * const listi = getListIntf();
            size_t size = listi->list_size(reactor->channels);
            for(size_t i = 0; i < size; i++)
            {
              OsReactorChannel_t * channel = (OsReactorChannel_t *) listi->item_lookup_index(reactor->channels, i);
              if(channel == epoll_event.data.ptr)
              {
                // Unlock as soon as we have found our channel. A channel handler might want to unregister the channel.
                (void) thri->mutex_unlock(reactor->mutex);

                // Check which epoll event has occured
                if((epoll_event.events & EPOLLIN) || (epoll_event.events & EPOLLPRI))
                {
                  (void) osreactor_channel_handle(OSREACTORCHANNELSTATE_READ, channel);
                }
                else if(epoll_event.events & EPOLLOUT)
                {
                  (void) osreactor_channel_handle(OSREACTORCHANNELSTATE_WRITE, channel);
                }
                else if((epoll_event.events & EPOLLRDHUP) || (epoll_event.events & EPOLLERR) || (epoll_event.events & EPOLLRDHUP))
                {
                  (void) osreactor_reactor_channel_unregister(reactor, channel);
                }
                break;
              }
            }
          }
        }          
      }
      else
      {
        const char_t * error = strerror(errno);
        ERROR("epoll wait error: %s\n", error);
      }
    }
  }

  return NULL;
}
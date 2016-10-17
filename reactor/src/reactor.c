#include "reactor.h"

#include <logging/logging.h>
#include <osa/osmemIntf.h>
#include <osa/osthreadingIntf.h>
#include <collection/listIntf.h>
#include <osa/osepollIntf.h>

struct Reactor
{
  enum ReactorState
  {
    REACTORSTATE_UNKNOWN = 0,
    REACTORSTATE_START,
    REACTORSTATE_RUN,
    REACTORSTATE_STOP
  } state;
  List_t * channels;
  OsThread_t * thread;
  OsMutex_t * mutex;
  int32_t epollfd;
};

static void * localReactorThread(void * data);

Status_e reactor_reactor_create(Reactor_t ** reactor)
{
  Status_e rc = STATUS_FAILURE;

  if(reactor != NULL)
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    *reactor = (struct Reactor *) memi->malloc(sizeof(struct Reactor));
    if(*reactor != NULL)
    {
      Boolean_e allOk = BOOLEAN_TRUE;
      const ListIntf_t * const listi = getListIntf();
      if(listi->list_create(&(*reactor)->channels, (ListItemDestructor_t) reactor_channel_destroy) == STATUS_SUCCESS)
      {
        const OsThreadingIntf_t * const thri = getOsThreadingIntf();
        if(thri->mutex_create(&(*reactor)->mutex) == STATUS_SUCCESS)
        {
          const OsEpollIntf_t * const epolli = getOsEpollIntf();
          if(epolli->create(&(*reactor)->epollfd) == STATUS_SUCCESS)
          {
            (*reactor)->state = REACTORSTATE_START;
            if(thri->thread_create(&(*reactor)->thread, localReactorThread, *reactor) == STATUS_SUCCESS)
            {
              DEBUG("Reactor started\n");
              rc = STATUS_SUCCESS;
            }
            else
            {
              allOk = BOOLEAN_FALSE;
            }

            if(allOk == BOOLEAN_FALSE)
            {
              (void) epolli->close((*reactor)->epollfd);
            }
          }
          else
          {
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

Status_e reactor_reactor_channel_register(Reactor_t * reactor, ReactorChannel_t * channel)
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
        int32_t fd = getOsNetIntf()->socket_fd(reactor_channel_get_socket(channel));
        OsEpollEvent_t epoll_event;
        epoll_event.events = OSEPOLLEVENT_IN | OSEPOLLEVENT_OUT | OSEPOLLEVENT_RDHUP | OSEPOLLEVENT_PRI | OSEPOLLEVENT_ERR | OSEPOLLEVENT_HUP | OSEPOLLEVENT_ET;
        epoll_event.data = channel;
        if(getOsEpollIntf()->ctl_add(reactor->epollfd, fd, &epoll_event) == STATUS_SUCCESS)
        {
          rc = STATUS_SUCCESS;
        }
        else
        {
          (void) listi->item_remove_index(reactor->channels, listi->list_size(reactor->channels) - 1);
        }
      }

      (void) thri->mutex_unlock(reactor->mutex);
    }
  }

  return rc;
}

Status_e reactor_reactor_channel_unregister(Reactor_t * reactor, ReactorChannel_t * channel)
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
        ReactorChannel_t * item = (ReactorChannel_t *) listi->item_lookup_index(reactor->channels, i);
        if(channel == item)
        {
          int32_t fd = getOsNetIntf()->socket_fd(reactor_channel_get_socket(channel));
          if(getOsEpollIntf()->ctl_del(reactor->epollfd, fd) == STATUS_SUCCESS)
          {
            rc = listi->item_remove_index(reactor->channels, i);
          }
          break;
        }
      }

      (void) thri->mutex_unlock(reactor->mutex);
    }
  }

  return rc;
}

Status_e reactor_reactor_destroy(Reactor_t * reactor)
{
  Status_e rc = STATUS_FAILURE;

  if(reactor != NULL)
  {
    reactor->state = REACTORSTATE_STOP;

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

          const OsEpollIntf_t * const epolli = getOsEpollIntf();
          if(epolli->close(reactor->epollfd) == STATUS_SUCCESS)
          {
            reactor->epollfd = -1;

            const OsMemIntf_t * const memi = getOsMemIntf();
            memi->free(reactor);

            rc = STATUS_SUCCESS;
          }
        }
      }
    }
  }

  return rc;
}

static void * localReactorThread(void * data)
{
  Reactor_t * reactor = (Reactor_t *) data;

  if(reactor != NULL)
  {
    if(reactor->state == REACTORSTATE_START)
    {
      reactor->state = REACTORSTATE_RUN;
    }

    while(reactor->state == REACTORSTATE_RUN)
    {
      const OsThreadingIntf_t * const thri = getOsThreadingIntf();

      OsEpollEvent_t epoll_event;
      if(getOsEpollIntf()->wait(reactor->epollfd, &epoll_event) == STATUS_SUCCESS)
      {
        if(!(epoll_event.events & OSEPOLLEVENT_TIMEOUT))
        {
          if(thri->mutex_lock(reactor->mutex) == STATUS_SUCCESS)
          {
            const ListIntf_t * const listi = getListIntf();
            size_t size = listi->list_size(reactor->channels);
            for(size_t i = 0; i < size; i++)
            {
              ReactorChannel_t * channel = (ReactorChannel_t *) listi->item_lookup_index(reactor->channels, i);
              if(channel == epoll_event.data)
              {
                // Unlock as soon as we have found our channel. A channel handler might want to unregister the channel.
                (void) thri->mutex_unlock(reactor->mutex);

                // Check which epoll event has occured
                if((epoll_event.events & OSEPOLLEVENT_IN) || (epoll_event.events & OSEPOLLEVENT_PRI))
                {
                  (void) reactor_channel_handle(REACTORCHANNELSTATE_READ, channel);
                }
                else if(epoll_event.events & OSEPOLLEVENT_OUT)
                {
                  (void) reactor_channel_handle(REACTORCHANNELSTATE_WRITE, channel);
                }
                else if((epoll_event.events & OSEPOLLEVENT_RDHUP) || (epoll_event.events & OSEPOLLEVENT_ERR) || (epoll_event.events & OSEPOLLEVENT_RDHUP))
                {
                  (void) reactor_reactor_channel_unregister(reactor, channel);
                }
                break;
              }
            }
          }
        }
      }
    }
  }

  return NULL;
}

#include "eventbus.h"

#include <logging/logging.h>
#include <osa/osmemIntf.h>
#include <osa/osthreadingIntf.h>
#include <osa/osutilsIntf.h>
#include <collection/listIntf.h>

struct EventBus
{
  enum EventBusState
  {
    EVENTBUSSTATE_UNKNOWN = 0,
    EVENTBUSSTATE_START,
    EVENTBUSSTATE_RUN,
    EVENTBUSSTATE_STOP
  } state;
  List_t *events;
  OsThread_t *thread;
  OsMutex_t *mutex;
};

static void * localEventBusThread(void * data);

Status_e eventbus_bus_create(EventBus_t ** bus)
{
  Status_e rc = STATUS_FAILURE;

  if(bus != NULL)
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    *bus = (struct EventBus *) memi->malloc(sizeof(struct EventBus));
    if(*bus != NULL)
    {
      Boolean_e allOk = BOOLEAN_TRUE;
      const ListIntf_t * const listi = getListIntf();
      if(listi->list_create(&(*bus)->events, (ListItemDestructor_t) eventbus_event_destroy) == STATUS_SUCCESS)
      {
        const OsThreadingIntf_t * const thri = getOsThreadingIntf();
        if(thri->mutex_create(&(*bus)->mutex) == STATUS_SUCCESS)
        {
          (*bus)->state = EVENTBUSSTATE_START;
          if(thri->thread_create(&(*bus)->thread, localEventBusThread, *bus) == STATUS_SUCCESS)
          {
            DEBUG("EventBus started\n");
            rc = STATUS_SUCCESS;
          }
          else
          {
            allOk = BOOLEAN_FALSE;
          }

          if(allOk == BOOLEAN_FALSE)
          {
            (void) thri->mutex_destroy((*bus)->mutex);
          }
        }
        else
        {
          allOk = BOOLEAN_FALSE;
        }

        if(allOk == BOOLEAN_FALSE)
        {
          (void) listi->list_destroy((*bus)->events);
        }
      }
      else
      {
        allOk = BOOLEAN_FALSE;
      }

      if(allOk == BOOLEAN_FALSE)
      {
        memi->free(*bus);
      }
    }
  }

  return rc;
}

Status_e eventbus_bus_send(EventBus_t *bus, Event_t *event)
{
  Status_e rc = STATUS_FAILURE;

  if((bus != NULL) && (event != NULL))
  {
    const OsThreadingIntf_t * const thri = getOsThreadingIntf();
    if(thri->mutex_lock(bus->mutex) == STATUS_SUCCESS)
    {
      const ListIntf_t * const listi = getListIntf();
      if(listi->item_append(bus->events, event) == STATUS_SUCCESS)
      {
        rc = STATUS_SUCCESS;
      }

      (void) thri->mutex_unlock(bus->mutex);
    }
  }

  return rc;
}

Status_e eventbus_bus_destroy(EventBus_t *bus)
{
  Status_e rc = STATUS_FAILURE;

  if(bus != NULL)
  {
    bus->state = EVENTBUSSTATE_STOP;

    const OsThreadingIntf_t * const thri = getOsThreadingIntf();
    if(thri->thread_destroy(bus->thread) == STATUS_SUCCESS)
    {
      bus->thread = NULL;

      if(thri->mutex_destroy(bus->mutex) == STATUS_SUCCESS)
      {
        bus->mutex = NULL;

        const ListIntf_t * const listi = getListIntf();
        if(listi->list_destroy(bus->events) == STATUS_SUCCESS)
        {
          bus->events = NULL;

          const OsMemIntf_t * const memi = getOsMemIntf();

          memi->free(bus);

          rc = STATUS_SUCCESS;
        }
      }
    }
  }

  return rc;
}

static void * localEventBusThread(void * data)
{
  EventBus_t *bus = (EventBus_t*) data;

  if(bus != NULL)
  {
    if(bus->state == EVENTBUSSTATE_START)
    {
      bus->state = EVENTBUSSTATE_RUN;
    }

    while(bus->state == EVENTBUSSTATE_RUN)
    {
      const OsThreadingIntf_t * const thri = getOsThreadingIntf();
      if(thri->mutex_lock(bus->mutex) == STATUS_SUCCESS)
      {
        const ListIntf_t * const listi = getListIntf();
        Event_t *event = (Event_t *) listi->item_lookup_index(bus->events, 0);
        if(event != NULL)
        {
          /* Unlock as soon as we have found an event.
           * An event might want to send an event again.
           */
          (void) thri->mutex_unlock(bus->mutex);
          (void) getEventBusIntf()->event_handle(event);
          if(thri->mutex_lock(bus->mutex) == STATUS_SUCCESS)
          {
            (void) listi->item_remove_index(bus->events, 0);
            (void) thri->mutex_unlock(bus->mutex);
            /* Reduce processor useage: sleep 1ms */
            (void) getOsUtilsIntf()->sleep_usec(1000);
          }
        }
        else
        {
          (void) thri->mutex_unlock(bus->mutex);
          /* Eventbus was empty: sleep 10ms */
          (void) getOsUtilsIntf()->sleep_usec(10000);
        }
      }
    }
  }

  return NULL;
}

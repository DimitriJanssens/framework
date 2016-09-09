#include "eventbus.h"

#include <osa/osmemIntf.h>

struct Event
{
  void * data;
  EventHandler_t handler;
  EventDataDestructor_t destructor;
};

Status_e eventbus_event_create(Event_t ** event, void * data, EventHandler_t handler, EventDataDestructor_t destructor)
{
  Status_e rc = STATUS_FAILURE;

  if(event != NULL)
  {
    if(handler != NULL)
    {
      if((data == NULL) || ((data != NULL) && (destructor != NULL)))
      {
        const OsMemIntf_t * const memi = getOsMemIntf();
        *event = (struct Event *) memi->malloc(sizeof(struct Event));
        if(*event != NULL)
        {
          (*event)->data = data;
          (*event)->handler = handler;
          (*event)->destructor = destructor;

          rc = STATUS_SUCCESS;
        }
      }
    }
  }

  return rc;

}

Status_e eventbus_event_handle(Event_t * event)
{
  Status_e rc = STATUS_FAILURE;

  if(event != NULL)
  {
    event->handler(event->data);
    rc = STATUS_SUCCESS;
  }

  return rc;
}

Status_e eventbus_event_destroy(Event_t * event)
{
  Status_e rc = STATUS_FAILURE;

  if(event != NULL)
  {
    const OsMemIntf_t * memi = getOsMemIntf();

    if(event->data != NULL)
    {
      event->destructor(event->data);
    }

    event->handler = NULL;
    event->data = NULL;

    memi->free(event);
    
    rc = STATUS_SUCCESS;
  }

  return rc;
}
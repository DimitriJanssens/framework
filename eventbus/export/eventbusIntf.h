#ifndef EVENTBUSINTF_H
#define EVENTBUSINTF_H

#include <common/commontypes.h>

typedef struct EventBus EventBus_t;
typedef struct Event Event_t;
typedef void (*EventHandler_t)(const void * const data);
typedef void (*EventDataDestructor_t)(void * data);

typedef struct
{
  Status_e (*bus_create)(EventBus_t ** bus);
  Status_e (*bus_send)(EventBus_t *bus, Event_t *event);
  Status_e (*bus_destroy)(EventBus_t *bus);

  Status_e (*event_create)(Event_t ** event, void * data, EventHandler_t handler, EventDataDestructor_t destructor);
  Status_e (*event_handle)(Event_t *event);
  Status_e (*event_destroy)(Event_t *event);
} EventBusIntf_t;

EventBusIntf_t * getEventBusIntf(void);

#ifdef UNITTESTS
void setDefaultEventBusIntfForUnittests(void);
void resetDefaultEventBusIntfForUnittests(void);
#endif

#endif
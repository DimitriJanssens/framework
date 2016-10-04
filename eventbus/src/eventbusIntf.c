#include <eventbus/eventbusIntf.h>

#include "eventbus.h"

static EventBusIntf_t intf = {
  #ifndef UNITTESTS
  .bus_create = eventbus_bus_create,
  .bus_send = eventbus_bus_send,
  .bus_destroy = eventbus_bus_destroy,

  .event_create = eventbus_event_create,
  .event_handle = eventbus_event_handle,
  .event_destroy = eventbus_event_destroy,
  #else
  .bus_create = NULL,
  .bus_send = NULL,
  .bus_destroy = NULL,

  .event_create = NULL,
  .event_handle = NULL,
  .event_destroy = NULL,
  #endif
};

EventBusIntf_t * getEventBusIntf(void)
{
  return &intf;
}

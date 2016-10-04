#include "eventbus.h"

#ifdef UNITTESTS
void setDefaultEventBusIntfForUnittests(void)
{
  EventBusIntf_t * intf = getEventBusIntf();

  intf->bus_create = eventbus_bus_create;
  intf->bus_send = eventbus_bus_send;
  intf->bus_destroy = eventbus_bus_destroy;

  intf->event_create = eventbus_event_create;
  intf->event_handle = eventbus_event_handle;
  intf->event_destroy = eventbus_event_destroy;
}

void resetDefaultEventBusIntfForUnittests(void)
{
  EventBusIntf_t * intf = getEventBusIntf();

  intf->bus_create = NULL;
  intf->bus_send = NULL;
  intf->bus_destroy = NULL;

  intf->event_create = NULL;
  intf->event_handle = NULL;
  intf->event_destroy = NULL;
}
#endif

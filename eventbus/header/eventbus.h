#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <eventbus/eventbusIntf.h>

Status_e eventbus_bus_create(EventBus_t ** bus);
Status_e eventbus_bus_send(EventBus_t *bus, Event_t *event);
Status_e eventbus_bus_destroy(EventBus_t *bus);

Status_e eventbus_event_create(Event_t ** event, void * data, EventHandler_t handler, EventDataDestructor_t destructor);
Status_e eventbus_event_handle(Event_t *event);
Status_e eventbus_event_destroy(Event_t *event);
#endif
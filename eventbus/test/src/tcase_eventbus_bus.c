#include "test_eventbus_tcases.h"

#include "test_eventbus_helper.h"

START_TEST(test_bus_NULL)
  const EventBusIntf_t * const ebusi = getEventBusIntf();

  EventBus_t * bus = (EventBus_t *) 0x12345;
  Event_t * event = (Event_t *) 0x12345;

  ck_assert(ebusi->bus_create(NULL) == STATUS_FAILURE);
  ck_assert(ebusi->bus_send(NULL, NULL) == STATUS_FAILURE);
  ck_assert(ebusi->bus_send(bus, NULL) == STATUS_FAILURE);
  ck_assert(ebusi->bus_send(NULL, event) == STATUS_FAILURE);
  ck_assert(ebusi->bus_destroy(NULL) == STATUS_FAILURE);
END_TEST

static EventBus_t * localCreateBus(void)
{
  EventBus_t * rc = NULL;
  ck_assert(getEventBusIntf()->bus_create(&rc) == STATUS_SUCCESS);
  return rc;
}

static void localDestroyBus(EventBus_t * bus)
{
  ck_assert(getEventBusIntf()->bus_destroy(bus) == STATUS_SUCCESS);
}

START_TEST(test_bus_create_destroy)
  localDestroyBus(localCreateBus());
END_TEST

#define EVENTCOUNTER  500

static void localEventHandler(const void * const data)
{
  ck_assert(data != NULL);
  int * impl = (int*)data;
  (*impl)++;
}

static void localDummyEventDataDestructor(void * data)
{
  (void) data;
}

START_TEST(test_bus_create_send_destroy_nowait)
  const EventBusIntf_t * const ebusi = getEventBusIntf();

  EventBus_t * bus = localCreateBus();
  Event_t * events[EVENTCOUNTER];

  int data = 0;

  for(size_t i = 0; i < ARRAY_SIZE(events); i++)
    ck_assert(ebusi->event_create(&events[i], &data, localEventHandler, localDummyEventDataDestructor) == STATUS_SUCCESS);

  for(size_t i = 0; i < ARRAY_SIZE(events); i++)
    ck_assert(ebusi->bus_send(bus, events[i]) == STATUS_SUCCESS);

  localDestroyBus(bus);

  ck_assert(data < EVENTCOUNTER);
END_TEST

START_TEST(test_bus_create_send_destroy_wait)
  const EventBusIntf_t * const ebusi = getEventBusIntf();

  EventBus_t * bus = localCreateBus();
  Event_t * events[EVENTCOUNTER];

  int data = 0;
  for(size_t i = 0; i < ARRAY_SIZE(events); i++)
    ck_assert(ebusi->event_create(&events[i], &data, localEventHandler, localDummyEventDataDestructor) == STATUS_SUCCESS);

  for(size_t i = 0; i < ARRAY_SIZE(events); i++)
    ck_assert(ebusi->bus_send(bus, events[i]) == STATUS_SUCCESS);

  while(data != EVENTCOUNTER);

  localDestroyBus(bus);
  ck_assert(data == EVENTCOUNTER);
END_TEST

TCase * tcase_eventbus_bus(void)
{
  TCase *tc = tcase_create("TestCase EventBus Bus");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_eventbus_setup, test_eventbus_teardown);

  tcase_add_test(tc, test_bus_NULL);
  tcase_add_test(tc, test_bus_create_destroy);
  tcase_add_test(tc, test_bus_create_send_destroy_nowait);
  tcase_add_test(tc, test_bus_create_send_destroy_wait);

  return tc;
}
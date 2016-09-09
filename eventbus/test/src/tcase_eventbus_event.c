#include "test_eventbus_tcases.h"

#include <osa/osmemIntf.h>

#include "test_eventbus_helper.h"

START_TEST(test_event_NULL)
  const EventBusIntf_t * const ebusi = getEventBusIntf();

  Event_t * event = (Event_t *) 0x12345;
  void * data = (void *) 0x12345;
  EventHandler_t handler = (EventHandler_t) 0x12345;
  EventDataDestructor_t destr = (EventDataDestructor_t) 0x12345;

  ck_assert(ebusi->event_create(NULL, NULL, NULL, NULL) == STATUS_FAILURE);
  ck_assert(ebusi->event_create(&event, NULL, NULL, NULL) == STATUS_FAILURE);
  ck_assert(ebusi->event_create(NULL, NULL, handler, NULL) == STATUS_FAILURE);
  ck_assert(ebusi->event_create(NULL, data, NULL, destr) == STATUS_FAILURE);
  ck_assert(ebusi->event_create(&event, data, handler, NULL) == STATUS_FAILURE);
  ck_assert(ebusi->event_destroy(NULL) == STATUS_FAILURE);
END_TEST

static void localEventHandlerNoData(const void * const data)
{
  ck_assert(data == NULL);
}

START_TEST(test_event_create_handle_destroy_nodata)
  const EventBusIntf_t * const ebusi = getEventBusIntf();

  Event_t * event;
  ck_assert(ebusi->event_create(&event, NULL, localEventHandlerNoData, NULL) == STATUS_SUCCESS);

  ck_assert(ebusi->event_handle(event) == STATUS_SUCCESS);

  ck_assert(ebusi->event_destroy(event) == STATUS_SUCCESS);

END_TEST

static void localEventHandlerData(const void * const data)
{
  ck_assert(data != NULL);
}

static void localEventDataDestructor(void * data)
{
  ck_assert(data != NULL);
  getOsMemIntf()->free(data);
}

START_TEST(test_event_create_handle_destroy_data)
  const EventBusIntf_t * const ebusi = getEventBusIntf();

  void * data = getOsMemIntf()->malloc(1024);

  Event_t * event;
  ck_assert(ebusi->event_create(&event, data, localEventHandlerData, localEventDataDestructor) == STATUS_SUCCESS);

  ck_assert(ebusi->event_handle(event) == STATUS_SUCCESS);

  ck_assert(ebusi->event_destroy(event) == STATUS_SUCCESS);

END_TEST

TCase * tcase_eventbus_event(void)
{
  TCase *tc = tcase_create("TestCase EventBus Event");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_eventbus_setup, test_eventbus_teardown);

  tcase_add_test(tc, test_event_NULL);
  tcase_add_test(tc, test_event_create_handle_destroy_nodata);
  tcase_add_test(tc, test_event_create_handle_destroy_data);

  return tc;
}
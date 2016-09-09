#include "test_osthreading_tcases.h"

#include <logging/logging.h>

#include "test_osthreading_helper.h"

START_TEST(test_thread_NULL)
  const OsThreadingIntf_t *const thri = getOsThreadingIntf();

  OsThread_t * t = (OsThread_t *) 0x12345;
  ThreadExecutor_t exec = (ThreadExecutor_t) 0x12345;
  
  ck_assert(thri->thread_create(NULL, NULL, NULL) == STATUS_FAILURE);
  ck_assert(thri->thread_create(&t, NULL, NULL) == STATUS_FAILURE);
  ck_assert(thri->thread_create(NULL, exec, NULL) == STATUS_FAILURE);

  ck_assert(thri->thread_destroy(NULL) == STATUS_FAILURE);

  ck_assert(thri->thread_join(NULL) == STATUS_FAILURE);
END_TEST

static void * mythreadworker1(void *data)
{
  ck_assert(data == NULL);
  INFO("Printing from inside my thread\n");
  return NULL;
}

START_TEST(test_thread_create_destroy)
  const OsThreadingIntf_t *const thri = getOsThreadingIntf();
  OsThread_t * thread;
  ck_assert(thri->thread_create(&thread, mythreadworker1, NULL) == STATUS_SUCCESS);
  ck_assert(thri->thread_destroy(thread) == STATUS_SUCCESS);
END_TEST

START_TEST(test_thread_yield)
  ck_assert(getOsThreadingIntf()->thread_yield() == STATUS_SUCCESS);
END_TEST

static void * mythreadworker2(void *data)
{
  ck_assert(data != NULL);

  uint16_t *pitspoes = (uint16_t *)data;
  INFO("THREAD: counter start\n");

  for(uint8_t i = 1; i != 0; i++)
  {
    *pitspoes = i;
  }

  INFO("THREAD: counter stopped\n");

  *pitspoes = (uint16_t)~0;
  
  return NULL;
}

START_TEST(test_thread_join)
  const OsThreadingIntf_t *const thri = getOsThreadingIntf();
  OsThread_t * thread;
  uint16_t pitspoes = 0;
  ck_assert(thri->thread_create(&thread, mythreadworker2, &pitspoes) == STATUS_SUCCESS);

  INFO("Waiting for thread to start\n");
  while(pitspoes == 0)
  {
    thri->thread_yield();
  }

  INFO("Waiting for thread to stop\n");
  ck_assert(thri->thread_join(thread) == STATUS_SUCCESS);
  ck_assert(pitspoes == (uint16_t)~0);

  INFO("Thread has stopped!\n")
  ck_assert(thri->thread_destroy(thread) == STATUS_SUCCESS);
END_TEST

TCase *tcase_osthreading_thread(void)
{
	TCase *tc = tcase_create("TestCase OsThreading Thread");
	tcase_set_timeout(tc, 10);
	tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osthreading_setup, test_osthreading_teardown);

  tcase_add_test(tc, test_thread_NULL);
  tcase_add_test(tc, test_thread_create_destroy);
  tcase_add_test(tc, test_thread_yield);
  tcase_add_test(tc, test_thread_join);

	return tc;
}
#include "test_osthreading_tcases.h"

#include <logging/logging.h>

#include "test_osthreading_helper.h"

START_TEST(test_condition_NULL)
  const OsThreadingIntf_t * const thri = getOsThreadingIntf();
  ck_assert(thri->condition_create(NULL) == STATUS_FAILURE);
  ck_assert(thri->condition_signal(NULL) == STATUS_FAILURE);
  ck_assert(thri->condition_wait(NULL, NULL) == STATUS_FAILURE);
  ck_assert(thri->condition_destroy(NULL) == STATUS_FAILURE);
END_TEST

struct _threaddata
{
  OsCondition_t * c;
  OsMutex_t * m;
  uint8_t counter;
};

static void * localThreadWorker(void * data)
{
  ck_assert(data != NULL);
  struct _threaddata * tdata = (struct _threaddata *) data;

  const OsThreadingIntf_t * const thri = getOsThreadingIntf();

  while(tdata->counter > 0)
  {
    ck_assert(thri->mutex_lock(tdata->m) == STATUS_SUCCESS);
    tdata->counter--;

    if(tdata->counter == 0)
    {
      INFO("THEAD B: signaling condition\n");
      ck_assert(thri->condition_signal(tdata->c) == STATUS_SUCCESS);
    }

    ck_assert(thri->mutex_unlock(tdata->m) == STATUS_SUCCESS);
  }

  return NULL;
}

START_TEST(test_condition_threading)
  const OsThreadingIntf_t * const thri = getOsThreadingIntf();
  OsThread_t * t;
  OsCondition_t * c;
  OsMutex_t * m;
  ck_assert(thri->condition_create(&c) == STATUS_SUCCESS);
  ck_assert(thri->mutex_create(&m) == STATUS_SUCCESS);

  INFO("THEAD A: waiting for condition\n");
  ck_assert(thri->mutex_lock(m) == STATUS_SUCCESS);

  struct _threaddata data;
  data.c = c;
  data.m = m;
  data.counter = 255;
  ck_assert(thri->thread_create(&t, localThreadWorker, &data) == STATUS_SUCCESS);

  ck_assert(thri->condition_wait(c, m) == STATUS_SUCCESS);
  INFO("THEAD A: condition received\n");
  
  ck_assert(data.counter == 0);
  ck_assert(thri->mutex_trylock(m) == STATUS_FAILURE);
  ck_assert(thri->mutex_unlock(m) == STATUS_SUCCESS);

  ck_assert(thri->mutex_destroy(m) == STATUS_SUCCESS);
  ck_assert(thri->condition_destroy(c) == STATUS_SUCCESS);
  ck_assert(thri->thread_destroy(t) == STATUS_SUCCESS);
END_TEST

TCase *tcase_osthreading_condition(void)
{
  TCase *tc = tcase_create("TestCase OsThreading Condition");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osthreading_setup, test_osthreading_teardown);

  tcase_add_test(tc, test_condition_NULL);
  tcase_add_test(tc, test_condition_threading);

  return tc;
}
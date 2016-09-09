#include "test_osthreading_tcases.h"

#include <logging/logging.h>

#include "test_osthreading_helper.h"

START_TEST(test_mutex_NULL)
  const OsThreadingIntf_t * const thri = getOsThreadingIntf();
  ck_assert(thri->mutex_create(NULL) == STATUS_FAILURE);
  ck_assert(thri->mutex_lock(NULL) == STATUS_FAILURE);
  ck_assert(thri->mutex_trylock(NULL) == STATUS_FAILURE);
  ck_assert(thri->mutex_unlock(NULL) == STATUS_FAILURE);
  ck_assert(thri->mutex_destroy(NULL) == STATUS_FAILURE);
END_TEST

START_TEST(test_mutex_lock_trylock_unlock)
  OsMutex_t * m;
  const OsThreadingIntf_t * const thri = getOsThreadingIntf();
  ck_assert(thri->mutex_create(&m) == STATUS_SUCCESS);
  ck_assert(thri->mutex_lock(m) == STATUS_SUCCESS);
  ck_assert(thri->mutex_trylock(m) == STATUS_FAILURE);
  ck_assert(thri->mutex_unlock(m) == STATUS_SUCCESS);
  ck_assert(thri->mutex_destroy(m) == STATUS_SUCCESS);
END_TEST

struct _threaddata
{
  OsMutex_t * m;
  uint8_t counter;
};

static void * localThreadWorker(void * data)
{
  ck_assert(data != NULL);
  struct _threaddata * tdata = ((struct _threaddata *)data);
  ck_assert(tdata != NULL);

  const OsThreadingIntf_t * const thri = getOsThreadingIntf();

  while(tdata->counter > 0)
  {
    ck_assert(thri->mutex_lock(tdata->m) == STATUS_SUCCESS);
    if(tdata->counter%255 == 0)
    {
      INFO("THREAD B: obtained mutex lock.\n");
    }
    
    tdata->counter--;

    ck_assert(thri->mutex_unlock(tdata->m) == STATUS_SUCCESS);
    if(tdata->counter%255 == 0)
    {
      INFO("THREAD B: released mutex lock.\n");
    }
  }

  return NULL;
}

START_TEST(test_mutex_threading)
  OsThread_t * t;
  OsMutex_t * m;
  const OsThreadingIntf_t * const thri = getOsThreadingIntf();
  ck_assert(thri->mutex_create(&m) == STATUS_SUCCESS);

  struct _threaddata data;
  data.m = m;
  data.counter = 255;
  ck_assert(thri->thread_create(&t, localThreadWorker, &data) == STATUS_SUCCESS);

  while(data.counter > 0)
  {
    ck_assert(thri->mutex_lock(m) == STATUS_SUCCESS);
    if(data.counter%255 == 0)
    {
      INFO("THREAD A: obtained mutex lock.\n");
    }

    ck_assert(thri->mutex_unlock(m) == STATUS_SUCCESS);
    if(data.counter%255 == 0)
    {
      INFO("THREAD A: released mutex lock.\n");
    }
  }

  ck_assert(thri->mutex_lock(m) == STATUS_SUCCESS);
  INFO("THREAD A: regained mutex final lock.\n");

  ck_assert(thri->mutex_unlock(m) == STATUS_SUCCESS);

  ck_assert(thri->mutex_destroy(m) == STATUS_SUCCESS);

  ck_assert(thri->thread_destroy(t) == STATUS_SUCCESS);
END_TEST

TCase *tcase_osthreading_mutex(void)
{
	TCase *tc = tcase_create("TestCase OsThreading Mutex");
	tcase_set_timeout(tc, 10);
	tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_osthreading_setup, test_osthreading_teardown);

  tcase_add_test(tc, test_mutex_NULL);
  tcase_add_test(tc, test_mutex_lock_trylock_unlock);
  tcase_add_test(tc, test_mutex_threading);

	return tc;
}
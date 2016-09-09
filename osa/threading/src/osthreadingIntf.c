#include <osa/osthreadingIntf.h>

#include "osthreading.h"

static OsThreadingIntf_t intf = {
	#ifndef UNITTESTS
	.thread_create = osthreading_thread_create,
	.thread_join = osthreading_thread_join,
	.thread_yield = osthreading_thread_yield,
	.thread_destroy = osthreading_thread_destroy,

	.mutex_create = osthreading_mutex_create,
  .mutex_lock = osthreading_mutex_lock,
  .mutex_trylock = osthreading_mutex_trylock,
  .mutex_unlock = osthreading_mutex_unlock,
  .mutex_destroy = osthreading_mutex_destroy,

  .condition_create = osthreading_condition_create,
  .condition_signal = osthreading_condition_signal,
  .condition_wait = osthreading_condition_wait,
  .condition_destroy = osthreading_condition_destroy,

	#else
	.thread_create = NULL,
	.thread_join = NULL,
	.thread_yield = NULL,
	.thread_destroy = NULL,

	.mutex_create = NULL,
  .mutex_lock = NULL,
  .mutex_trylock = NULL,
  .mutex_unlock = NULL,
  .mutex_destroy = NULL,

  .condition_create = NULL,
  .condition_signal = NULL,
  .condition_wait = NULL,
  .condition_destroy = NULL,
 	#endif
};

OsThreadingIntf_t *getOsThreadingIntf(void)
{
	return &intf;
}

#ifdef UNITTESTS
void setDefaultOsThreadingIntfForUnittests(void)
{
  OsThreadingIntf_t * intf = getOsThreadingIntf();
  intf->thread_create = osthreading_thread_create;
  intf->thread_join = osthreading_thread_join;
  intf->thread_yield = osthreading_thread_yield;
  intf->thread_destroy = osthreading_thread_destroy;

  intf->mutex_create = osthreading_mutex_create;
  intf->mutex_lock = osthreading_mutex_lock;
  intf->mutex_trylock = osthreading_mutex_trylock;
  intf->mutex_unlock = osthreading_mutex_unlock;
  intf->mutex_destroy = osthreading_mutex_destroy;

  intf->condition_create = osthreading_condition_create;
  intf->condition_signal = osthreading_condition_signal;
  intf->condition_wait = osthreading_condition_wait;
  intf->condition_destroy = osthreading_condition_destroy;
}

void resetDefaultOsThreadingIntfForUnittests(void)
{
  OsThreadingIntf_t * intf = getOsThreadingIntf();
  intf->thread_create = NULL;
  intf->thread_join = NULL;
  intf->thread_yield = NULL;
  intf->thread_destroy = NULL;

  intf->mutex_create = NULL;
  intf->mutex_lock = NULL;
  intf->mutex_trylock = NULL;
  intf->mutex_unlock = NULL;
  intf->mutex_destroy = NULL;

  intf->condition_create = NULL;
  intf->condition_signal = NULL;
  intf->condition_wait = NULL;
  intf->condition_destroy = NULL;
}
#endif
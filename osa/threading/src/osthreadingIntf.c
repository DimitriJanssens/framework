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

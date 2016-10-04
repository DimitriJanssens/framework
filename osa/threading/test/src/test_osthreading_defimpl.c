#include "osthreading.h"

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

#ifndef OSTHREADING_H
#define OSTHREADING_H

#include <osa/osthreadingIntf.h>
#include <pthread.h>

#define OSTHREADING_MAGIC   0xBEAFDEADU

struct OsThread
{
  Boolean_e joined;
  uint32_t magic;
  pthread_t thread;
  ThreadExecutor_t function;
  void *userData;
};

struct OsCondition
{
  uint32_t magic;
  pthread_cond_t condition;
};

struct OsMutex
{
  uint32_t magic;
  pthread_mutex_t mutex;
};

Status_e osthreading_thread_create(OsThread_t ** t, ThreadExecutor_t exec, void *data);
Status_e osthreading_thread_join(OsThread_t * t);
Status_e osthreading_thread_yield(void);
Status_e osthreading_thread_destroy(OsThread_t * t);

Status_e osthreading_mutex_create(OsMutex_t **m);
Status_e osthreading_mutex_lock(OsMutex_t * m);
Status_e osthreading_mutex_trylock(OsMutex_t * m);
Status_e osthreading_mutex_unlock(OsMutex_t * m);
Status_e osthreading_mutex_destroy(OsMutex_t * m);

Status_e osthreading_condition_create(OsCondition_t **c);
Status_e osthreading_condition_signal(OsCondition_t * c);
Status_e osthreading_condition_wait(OsCondition_t * c, OsMutex_t * m);
Status_e osthreading_condition_destroy(OsCondition_t * c);

#endif

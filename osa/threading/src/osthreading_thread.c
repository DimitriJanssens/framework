#include "osthreading.h"

#include <signal.h>
#include <sched.h>

#include <logging/logging.h>
#include <osa/osmemIntf.h>

static void *localStartThreadWithBlockedSignals(void *data);

Status_e osthreading_thread_create(OsThread_t **t, ThreadExecutor_t exec, void *data)
{
  Status_e rc = STATUS_FAILURE;

  if ((t != NULL) && (exec != NULL))
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    OsThread_t * newThread = (struct OsThread *) memi->malloc(sizeof(struct OsThread));
    if(newThread != NULL)
    {
      memi->memset(newThread, 0, sizeof(*newThread));

      newThread->function = exec;
      newThread->userData = data;

      if (pthread_create(&newThread->thread, NULL, localStartThreadWithBlockedSignals, newThread) == 0)
      {
        newThread->magic = OSTHREADING_MAGIC;
        newThread->joined = BOOLEAN_FALSE;
        *t = newThread;
        rc = STATUS_SUCCESS;
      }
      else
      {
        memi->free(newThread);
        newThread = NULL;
      }
    }
  }

  return rc;
}

Status_e osthreading_thread_join(OsThread_t * t)
{
  Status_e rc = STATUS_FAILURE;

  if ((t != NULL) && (t->magic == OSTHREADING_MAGIC))
  {
    /*
     * For unittesting to work properly (valgrind pthread option),
     * we check the joined state of the thread and will not join it twice
     */
    if(t->joined == BOOLEAN_FALSE)
    {
      if (pthread_join(t->thread, NULL) == 0)
      {
        t->joined = BOOLEAN_TRUE;
        rc = STATUS_SUCCESS;
      }
    }
    else
    {
        rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osthreading_thread_yield(void)
{
  return (sched_yield() == 0) ? STATUS_SUCCESS : STATUS_FAILURE;
}

Status_e osthreading_thread_destroy(OsThread_t * t)
{
  Status_e rc = STATUS_FAILURE;

  if ((t != NULL) && (t->magic == OSTHREADING_MAGIC))
  {
    if(getOsThreadingIntf()->thread_join(t) == STATUS_SUCCESS)
    {
      const OsMemIntf_t * const memi = getOsMemIntf();

      memi->memset(t, 0, sizeof(*t));
      memi->free(t);

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

static void *localStartThreadWithBlockedSignals(void *data)
{
  void *rc = NULL;

  OsThread_t * t = (OsThread_t *) data;
  if ((t != NULL) && (t->function != NULL))
  {
    sigset_t set;
    if (sigfillset(&set) == 0)
    {
      if (pthread_sigmask(SIG_SETMASK, &set, NULL) == 0)
      {
        rc = t->function(t->userData);
      }
    }
  }

  return rc;
}

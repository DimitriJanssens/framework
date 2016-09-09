#include "osthreading.h"

#include <osa/osmemIntf.h>

Status_e osthreading_mutex_create(OsMutex_t ** m)
{
  Status_e rc = STATUS_FAILURE;

  if (m != NULL)
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    OsMutex_t * newMutex = (struct OsMutex *) memi->malloc(sizeof(struct OsMutex));
    if (newMutex != NULL)
    {
      memi->memset(newMutex, 0, sizeof(*newMutex));
      if (pthread_mutex_init(&newMutex->mutex, NULL) == 0)
      {
        newMutex->magic = OSTHREADING_MAGIC;
        *m = newMutex;
        rc = STATUS_SUCCESS;
      }
      else
      {
        memi->free(newMutex);
      }
    }
  }

  return rc;
}

Status_e osthreading_mutex_lock(OsMutex_t * m)
{
  Status_e rc = STATUS_FAILURE;

  if ((m != NULL) && (m->magic == OSTHREADING_MAGIC))
  {
    if (pthread_mutex_lock(&m->mutex) == 0)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osthreading_mutex_unlock(OsMutex_t * m)
{
  Status_e rc = STATUS_FAILURE;

  if ((m != NULL) && (m->magic == OSTHREADING_MAGIC))
  {
    if (pthread_mutex_unlock(&m->mutex) == 0)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osthreading_mutex_trylock(OsMutex_t * m)
{
  Status_e rc = STATUS_FAILURE;

  if ((m != NULL) && (m->magic == OSTHREADING_MAGIC))
  {
    if (pthread_mutex_trylock(&m->mutex) == 0)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osthreading_mutex_destroy(OsMutex_t * m)
{
  Status_e rc = STATUS_FAILURE;

  if ((m != NULL) && (m->magic == OSTHREADING_MAGIC))
  {
    if(pthread_mutex_destroy(&m->mutex) == 0)
    {
      const OsMemIntf_t * const memi = getOsMemIntf();
      memi->memset(m, 0, sizeof(*m));
      memi->free(m);

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}
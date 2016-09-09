#include "osthreading.h"

#include <osa/osmemIntf.h>

Status_e osthreading_condition_create(OsCondition_t ** c)
{
  Status_e rc = STATUS_FAILURE;

  if (c != NULL)
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    OsCondition_t * newCondition = (struct OsCondition *) memi->malloc(sizeof(struct OsCondition));
    if (newCondition != NULL)
    {
      memi->memset(newCondition, 0, sizeof(struct OsCondition));
      if (pthread_cond_init(&newCondition->condition, NULL) == 0)
      {
        newCondition->magic = OSTHREADING_MAGIC;
        *c = (OsCondition_t *) newCondition;

        rc = STATUS_SUCCESS;
      }
      else
      {
        memi->free(newCondition);
      }
    }
  }

  return rc;
}

Status_e osthreading_condition_signal(OsCondition_t * c)
{
  Status_e rc = STATUS_FAILURE;

  if ((c != NULL) && (c->magic == OSTHREADING_MAGIC))
  {
    if (pthread_cond_signal(&c->condition) == 0)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osthreading_condition_wait(OsCondition_t * c, OsMutex_t * m)
{
  Status_e rc = STATUS_FAILURE;

  if ((c != NULL) && (m != NULL))
  {
    if ((c->magic == OSTHREADING_MAGIC) && (m->magic == OSTHREADING_MAGIC))
    {
      if (pthread_cond_wait(&c->condition, &m->mutex) == 0)
      {
        rc = STATUS_SUCCESS;
      }
    }
  }
  return rc;
}

Status_e osthreading_condition_destroy(OsCondition_t * c)
{
  Status_e rc = STATUS_FAILURE;

  if ((c != NULL) && (c->magic == OSTHREADING_MAGIC))
  {
    if(pthread_cond_destroy(&c->condition) == 0)
    {
      const OsMemIntf_t * const memi = getOsMemIntf();
      memi->memset(c, 0, sizeof(*c));
      memi->free(c);

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}
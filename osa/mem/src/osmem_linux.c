#include "osmem.h"

#include <stdlib.h>
#include <string.h>

void *osmem_malloc(size_t size)
{
  void *rc = NULL;

  if(size != 0)
  {
    rc = malloc(size);
  }

  return rc;
}

void osmem_free(void *ptr)
{
  free(ptr);
}

Status_e osmem_memset(void *s, int c, size_t n)
{
  Status_e rc = STATUS_FAILURE;

  if(s != NULL)
  {
    if(memset(s, c, n) == s)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osmem_memcpy(void *dest, const void *src, size_t n)
{
  Status_e rc = STATUS_FAILURE;

  if((dest != NULL) && (src != NULL))
  {
    if(memcpy(dest, src, n) == dest)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osmem_memcmp(const void *s1, const void *s2, size_t n)
{
  Status_e rc = STATUS_FAILURE;

  if((s1 != NULL) && (s2 != NULL))
  {
    if(memcmp(s1, s2, n) == 0)
    {
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

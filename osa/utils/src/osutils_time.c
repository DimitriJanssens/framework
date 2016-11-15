#include "osutils.h"

#include <time.h>

Status_e osutils_time_now(OsTime_t * now)
{
  Status_e rc = STATUS_FAILURE;

  if (now != NULL)
  {
    struct timespec t;
    if (clock_gettime(CLOCK_REALTIME, &t) == 0)
    {
      now->sec = t.tv_sec;
      now->nsec = t.tv_nsec;

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

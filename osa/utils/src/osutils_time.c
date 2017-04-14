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

Status_e osutils_date_utc(const OsTime_t * const now, OsDate_t * const date)
{
  Status_e rc = STATUS_FAILURE;

  if ((now != NULL) && (date != NULL))
  {
    const time_t secs = now->sec;
    struct tm t;
    if (gmtime_r(&secs, &t) != NULL)
    {
      date->seconds = t.tm_sec;
      date->minutes = t.tm_min;
      date->hours = t.tm_hour;
      date->day = t.tm_mday;
      date->month = t.tm_mon + 1;
      date->year = t.tm_year + 1900;

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e osutils_date_local(const OsTime_t * const now, OsDate_t * const date)
{
  Status_e rc = STATUS_FAILURE;

  if ((now != NULL) && (date != NULL))
  {
    const time_t secs = now->sec;
    struct tm t;
    if (localtime_r(&secs, &t) != NULL)
    {
      date->seconds = t.tm_sec;
      date->minutes = t.tm_min;
      date->hours = t.tm_hour;
      date->day = t.tm_mday;
      date->month = t.tm_mon;
      date->year = t.tm_year;

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

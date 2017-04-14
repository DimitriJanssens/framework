#include <osa/osutilsIntf.h>

#include "osutils.h"

static OsUtilsIntf_t intf =
{
  #ifndef UNITTESTS
  .sleep_sec = osutils_sleep_sec,
  .sleep_usec = osutils_sleep_usec,
  .sleep_nsec = osutils_sleep_nsec,
  .random = osutils_random,
  .time_now = osutils_time_now,
  .date_utc = osutils_date_utc,
  .date_local = osutils_date_local,
  .environ_get = osutils_environ_get,
  #else
  .sleep_sec = NULL,
  .sleep_usec = NULL,
  .sleep_nsec = NULL,
  .random = NULL,
  .time_now = NULL,
  .date_utc = NULL,
  .date_local = NULL,
  .environ_get = NULL,
  #endif
};

OsUtilsIntf_t * getOsUtilsIntf(void)
{
  return &intf;
}

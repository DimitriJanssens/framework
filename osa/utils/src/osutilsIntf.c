#include <osa/osutilsIntf.h>

#include "osutils.h"

static OsUtilsIntf_t intf =
{
  #ifndef UNITTESTS
  .sleep_sec = osutils_sleep_sec,
  .sleep_usec = osutils_sleep_usec,
  .sleep_nsec = osutils_sleep_nsec,
  #else
  .sleep_sec = NULL,
  .sleep_usec = NULL,
  .sleep_nsec = NULL,
  #endif
};

OsUtilsIntf_t * getOsUtilsIntf(void)
{
  return &intf;
}

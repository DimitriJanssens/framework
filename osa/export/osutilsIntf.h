#ifndef OSUTILSINTF_H
#define OSUTILSINTF_H

#include <common/commontypes.h>

typedef struct
{
  void (*sleep_sec)(uint32_t seconds);
  void (*sleep_usec)(uint32_t microseconds);
  void (*sleep_nsec)(uint32_t nanoseconds);
  uint32_t (*random)(void);
} OsUtilsIntf_t;

OsUtilsIntf_t * getOsUtilsIntf(void);

#ifdef UNITTESTS
void setDefaultOsUtilsIntfForUnittests(void);
void resetDefaultOsUtilsIntfForUnittests(void);
#endif

#endif

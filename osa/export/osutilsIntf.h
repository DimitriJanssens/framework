#ifndef OSUTILSINTF_H
#define OSUTILSINTF_H

#include <common/commontypes.h>

typedef struct
{
  uint32_t sec;
  uint32_t nsec;
} OsTime_t;

typedef struct
{
  uint32_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} OsDate_t;

typedef struct
{
  void (*sleep_sec)(uint32_t seconds);
  void (*sleep_usec)(uint32_t microseconds);
  void (*sleep_nsec)(uint32_t nanoseconds);
  uint32_t (*random)(void);
  Status_e (*time_now)(OsTime_t * const now);
  Status_e (*date_utc)(const OsTime_t * const now, OsDate_t * const date);
  Status_e (*date_local)(const OsTime_t * const now, OsDate_t * const date);
  const char_t * (*environ_get)(const char_t * name);
} OsUtilsIntf_t;

OsUtilsIntf_t * getOsUtilsIntf(void);

#ifdef UNITTESTS
void setDefaultOsUtilsIntfForUnittests(void);
void resetDefaultOsUtilsIntfForUnittests(void);
#endif

#endif

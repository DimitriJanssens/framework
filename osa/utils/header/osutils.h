#ifndef OSUTILS_H
#define OSUTILS_H

#include <osa/osutilsIntf.h>

void osutils_sleep_sec(uint32_t seconds);
void osutils_sleep_usec(uint32_t microseconds);
void osutils_sleep_nsec(uint32_t nanoseconds);

uint32_t osutils_random(void);

Status_e osutils_time_now(OsTime_t * const now);
Status_e osutils_date_utc(const OsTime_t * const now, OsDate_t * const date);
Status_e osutils_date_local(const OsTime_t * const now, OsDate_t * const date);

const char_t * osutils_environ_get(const char_t * name);

#endif

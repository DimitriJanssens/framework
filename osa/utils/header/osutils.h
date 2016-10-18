#ifndef OSUTILS_H
#define OSUTILS_H

#include <osa/osutilsIntf.h>

void osutils_sleep_sec(uint32_t seconds);
void osutils_sleep_usec(uint32_t microseconds);
void osutils_sleep_nsec(uint32_t nanoseconds);

uint32_t osutils_random(void);

#endif

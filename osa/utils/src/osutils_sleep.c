#include "osutils.h"

#include <unistd.h>
#include <time.h>

void osutils_sleep_sec(uint32_t seconds)
{
  sleep(seconds);
}

void osutils_sleep_usec(uint32_t microseconds)
{
  osutils_sleep_nsec(microseconds * 1000);
}

void osutils_sleep_nsec(uint32_t nanoseconds)
{
  struct timespec time;
  time.tv_sec = 0;
  time.tv_nsec = nanoseconds > 999999999 ? 999999999 : nanoseconds;
  nanosleep(&time, NULL);
}

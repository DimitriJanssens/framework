#ifndef LOGGING_H
#define LOGGING_H

#include <common/commontypes.h>

typedef struct
{
  Status_e (*init)(void);
  void (*info)(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...);
  void (*error)(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...);
  void (*debug)(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...);
  void (*teardown)(void);
} LoggingIntf_t;

const LoggingIntf_t * getLoggingIntf(void);

#if defined(UNITTESTS)

#include <stdio.h>
#define INFO(args...)       { printf("INFO: %s:%d: ", __FILE__, __LINE__); printf(args); }
#define ERROR(args...)      { printf("ERROR: %s:%d: ", __FILE__, __LINE__); printf(args); }
#define DEBUG(args...)      { printf("DEBUG: %s:%d: ", __FILE__, __LINE__); printf(args); }

#else

#define INFO(args...)       { getLoggingIntf()->info(__FILE__, sizeof(__FILE__), __func__, sizeof(__func__), __LINE__, args); }
#define ERROR(args...)      { getLoggingIntf()->error(__FILE__, sizeof(__FILE__), __func__, sizeof(__func__), __LINE__, args); }
#define DEBUG(args...)      { getLoggingIntf()->debug(__FILE__, sizeof(__FILE__), __func__, sizeof(__func__), __LINE__, args); }

#endif

#endif

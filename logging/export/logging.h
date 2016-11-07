#ifndef LOGGING_H
#define LOGGING_H

#include <common/commontypes.h>

typedef struct
{
  Status_e (*init)(void);
  void (*info)(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...);
  void (*error)(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...);
  void (*debug)(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...);
  void (*teardown)(void);
} LoggingIntf_t;

const LoggingIntf_t * getLoggingIntf(void);

#if defined(UNITTESTS)

#include <stdio.h>

#define INFO_SUBCAT(subcat, args...)       { printf("INFO %s: %s:%d: ", subcat, __FILE__, __LINE__); printf(args); }
#define ERROR_SUBCAT(subcat, args...)      { printf("ERROR %s: %s:%d: ", subcat, __FILE__, __LINE__); printf(args); }
#define DEBUG_SUBCAT(subcat, args...)      { printf("DEBUG %s: %s:%d: ", subcat, __FILE__, __LINE__); printf(args); }

#define INFO(args...)       { printf("INFO: %s:%d: ", __FILE__, __LINE__); printf(args); }
#define ERROR(args...)      { printf("ERROR: %s:%d: ", __FILE__, __LINE__); printf(args); }
#define DEBUG(args...)      { printf("DEBUG: %s:%d: ", __FILE__, __LINE__); printf(args); }

#else

#define INFO_SUBCAT(subcat, args...)       { getLoggingIntf()->info(subcat, __FILE__, sizeof(__FILE__), __func__, sizeof(__func__), __LINE__, args); }
#define ERROR_SUBCAT(subcat, args...)      { getLoggingIntf()->error(subcat, __FILE__, sizeof(__FILE__), __func__, sizeof(__func__), __LINE__, args); }
#define DEBUG_SUBCAT(subcat, args...)      { getLoggingIntf()->debug(subcat, __FILE__, sizeof(__FILE__), __func__, sizeof(__func__), __LINE__, args); }

#define INFO(args...)       INFO_SUBCAT(NULL, args)
#define ERROR(args...)      ERROR_SUBCAT(NULL, args)
#define DEBUG(args...)      DEBUG_SUBCAT(NULL, args)

#endif

#endif

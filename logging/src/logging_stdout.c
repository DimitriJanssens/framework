#include <logging/logging.h>

#include <stdio.h>
#include <stdarg.h>

static void logging_stdout_info(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...)
{
  (void) filesz;
  (void) funcsz;

  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  printf("INFO: %s:%s:%ld: ", file, func, line);
  vfprintf(stdout, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static void logging_stdout_error(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...)
{
  (void) filesz;
  (void) funcsz;

  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  printf("ERROR: %s:%s:%ld: ", file, func, line);
  vfprintf(stdout, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static void logging_stdout_debug(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...)
{
  (void) filesz;
  (void) funcsz;

  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  printf("DEBUG: %s:%s:%ld: ", file, func, line);
  vfprintf(stdout, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static const LoggingIntf_t intf =
{
  .init = NULL,
  .teardown = NULL,
  .info = logging_stdout_info,
  .error = logging_stdout_error,
  .debug = logging_stdout_debug,
};

const LoggingIntf_t * getLoggingIntf(void)
{
  return &intf;
}

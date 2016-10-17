#include <logging/logging.h>

#include <zlog/zlog.h>

extern const char *__progname;

static Status_e logging_zlog_init(void)
{
  Status_e rc = STATUS_FAILURE;

  if(dzlog_init(NULL, __progname) == 0)
  {
    INFO("Opened ZLOG framework for %s.\n", __progname);
    rc = STATUS_SUCCESS;
  }
  else
  {
    fprintf(stdout, "Unable to open ZLOG framework for %s!\n", __progname);
  }

  return rc;
}

static void logging_zlog_teardown(void)
{
  zlog_fini();
}

static void logging_zlog_info(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...)
{
  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  vdzlog(file, filesz-1, func, funcsz-1, line, ZLOG_LEVEL_INFO, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static void logging_zlog_error(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...)
{
  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  vdzlog(file, filesz-1, func, funcsz-1, line, ZLOG_LEVEL_ERROR, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static void logging_zlog_debug(const char * file, size_t filesz, const char * func, size_t funcsz, long line, const char * format, ...)
{
  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  vdzlog(file, filesz-1, func, funcsz-1, line, ZLOG_LEVEL_DEBUG, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static const LoggingIntf_t intf =
{
  .init = logging_zlog_init,
  .teardown = logging_zlog_teardown,
  .info = logging_zlog_info,
  .error = logging_zlog_error,
  .debug = logging_zlog_debug,
};

const LoggingIntf_t * getLoggingIntf(void)
{
  return &intf;
}

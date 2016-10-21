#include <logging/logging.h>

#include <zlog/zlog.h>

extern const char_t *__progname;

static Status_e logging_zlog_init(void)
{
  Status_e rc = STATUS_FAILURE;

  if(zlog_init(NULL) == 0)
  {
    INFO("Opened ZLOG framework.\n");
    rc = STATUS_SUCCESS;
  }
  else
  {
    fprintf(stdout, "Unable to open ZLOG framework for %s!\n", __progname);
  }

  return rc;
}

static zlog_category_t * logging_zlog_category(const char_t * subcategory)
{
  zlog_category_t * rc = NULL;

  if(subcategory == NULL)
  {
    rc = zlog_get_category(__progname);
  }
  else
  {
    char_t category[64] = { 0 };
    snprintf(category, ARRAY_SIZE(category), "%s_%s", __progname, subcategory);
    rc = zlog_get_category(category);
  }

  return rc;
}

static void logging_zlog_teardown(void)
{
  zlog_fini();
}

static void logging_zlog_info(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...)
{
  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);


  vzlog(logging_zlog_category(subcategory), file, filesz-1, func, funcsz-1, line, ZLOG_LEVEL_INFO, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static void logging_zlog_error(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...)
{
  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  vzlog(logging_zlog_category(subcategory), file, filesz-1, func, funcsz-1, line, ZLOG_LEVEL_ERROR, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static void logging_zlog_debug(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...)
{
  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  vzlog(logging_zlog_category(subcategory), file, filesz-1, func, funcsz-1, line, ZLOG_LEVEL_DEBUG, format, valist);

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

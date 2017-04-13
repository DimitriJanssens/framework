#include <logging/logging.h>

#include <stdio.h>
#include <stdarg.h>

extern const char_t *__progname;

static Status_e logging_stdout_init(void)
{
  return STATUS_SUCCESS;
}

static void logging_stdout_teardown(void)
{
}

static char_t * logging_stdout_category(const char_t * subcategory, char_t * buffer, size_t buffersize)
{
  char_t * rc = NULL;

  if(subcategory == NULL)
  {
    snprintf(buffer, buffersize, "%s", __progname);
    rc = buffer;
  }
  else
  {
    snprintf(buffer, buffersize, "%s_%s", __progname, subcategory);
    rc = buffer;
  }

  return rc;
}

static void logging_stdout_info(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...)
{
  (void) filesz;
  (void) funcsz;

  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  char_t category[64] = { 0 };
  logging_stdout_category(subcategory, category,ARRAY_SIZE(category));

  printf("INFO %s: %s:%s:%ld: ", category, file, func, line);
  vfprintf(stdout, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static void logging_stdout_error(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...)
{
  (void) filesz;
  (void) funcsz;

  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  char_t category[64] = { 0 };
  logging_stdout_category(subcategory, category,ARRAY_SIZE(category));

  printf("ERROR %s: %s:%s:%ld: ", category, file, func, line);
  vfprintf(stdout, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static void logging_stdout_debug(const char_t * subcategory, const char_t * file, size_t filesz, const char_t * func, size_t funcsz, long line, const char_t * format, ...)
{
  (void) filesz;
  (void) funcsz;

  va_list valist;
  /* initialize valist for num number of arguments */
  va_start(valist, format);

  char_t category[64] = { 0 };
  logging_stdout_category(subcategory, category,ARRAY_SIZE(category));

  printf("DEBUG %s: %s:%s:%ld: ", category, file, func, line);
  vfprintf(stdout, format, valist);

  /* clean memory reserved for valist */
  va_end(valist);
}

static const LoggingIntf_t intf =
{
  .init = logging_stdout_init,
  .teardown = logging_stdout_teardown,
  .info = logging_stdout_info,
  .error = logging_stdout_error,
  .debug = logging_stdout_debug,
};

const LoggingIntf_t * getLoggingIntf(void)
{
  return &intf;
}

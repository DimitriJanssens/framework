#include "osstring.h"

#include <logging/logging.h>

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>

Status_e osstring_write(char_t * str, size_t size, size_t * const written, const char_t * format, ...)
{
  Status_e rc = STATUS_FAILURE;

  if((str != NULL) && (format != NULL))
  {
    va_list valist;
    va_start(valist, format);

    int value = vsnprintf(str, size, format, valist);
    if(value < 0)
    {
      const char_t * error = strerror(errno);
      ERROR("vnsprintf: %s\n", error);
    }
    else
    {
      if((unsigned int) value < size)
      {
        if(written != NULL)
        {
          *written = value;
        }

        rc = STATUS_SUCCESS;
      }
      else if((unsigned int) value >= size)
      {
        if(written != NULL)
        {
          *written = 0;
        }

        ERROR("vnsprintf: buffersize too small!\n");
      }
    }

    va_end(valist);
  }

  return rc;
}

Status_e osstring_scan(const char_t * const str, size_t items, const char_t * format, ...)
{
  Status_e rc = STATUS_FAILURE;

  if((str != NULL) && (format != NULL))
  {
    va_list valist;
    va_start(valist, format);

    int value = vsscanf(str, format, valist);
    if(value < 0)
    {
      const char_t * error = strerror(errno);
      ERROR("vsscanf: %s\n", error);
    }
    else
    {
      if((unsigned int) value != items)
      {
        ERROR("vsscanf: unable to scan all expected items (%d vs %zu)\n", value, items);
      }
      else
      {
        rc = STATUS_SUCCESS;
      }
    }

    va_end(valist);
  }

  return rc;
}

size_t osstring_length(const char_t * str)
{
  size_t len = 0;

  if (str != NULL)
  {
    len = strlen(str);
  }

  return len;
}

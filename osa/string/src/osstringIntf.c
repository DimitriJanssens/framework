#include <osa/osstringIntf.h>

#include "osstring.h"

static OsStringIntf_t intf =
{
  #ifndef UNITTESTS
  .string_write = osstring_write,
  .string_length = osstring_length,
  #else
  .string_write = NULL,
  .string_length = NULL,
  #endif
};

OsStringIntf_t * getOsStringIntf(void)
{
  return &intf;
}

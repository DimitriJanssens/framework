#include <osa/osstringIntf.h>

#include "osstring.h"

static OsStringIntf_t intf =
{
  #ifndef UNITTESTS
  .string_cmp = osstring_cmp,
  .string_write = osstring_write,
  .string_scan = osstring_scan,
  .string_length = osstring_length,
  #else
  .string_cmp = NULL,
  .string_write = NULL,
  .string_scan = NULL,
  .string_length = NULL,
  #endif
};

OsStringIntf_t * getOsStringIntf(void)
{
  return &intf;
}

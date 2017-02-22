#include <osa/osfileIntf.h>

#include "osfile.h"

static OsFileIntf_t intf =
{
  #ifndef UNITTESTS
  .file_open = osfile_open,
  .file_size = osfile_size,
  .file_read = osfile_read,
  .file_write = osfile_write,
  .file_close = osfile_close,
  #else
  .file_open = NULL,
  .file_size = NULL,
  .file_read = NULL,
  .file_write = NULL,
  .file_close = NULL,
  #endif
};

OsFileIntf_t * getOsFileIntf(void)
{
  return &intf;
}

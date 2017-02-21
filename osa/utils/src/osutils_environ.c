#include "osutils.h"

#include <stdlib.h>

const char_t * osutils_environ_get(const char_t * name)
{
  const char_t * rc = NULL;
  if(name != NULL)
  {
    rc = getenv(name);
  }

  return rc;
}

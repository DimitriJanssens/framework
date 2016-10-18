#include "osutils.h"

#include <stdlib.h>
#include <time.h>

uint32_t osutils_random(void)
{
  static Boolean_e seeding = BOOLEAN_FALSE;

  if(seeding == BOOLEAN_FALSE)
  {
    srand(time(NULL));
    seeding = BOOLEAN_TRUE;
  }

  return rand();
}

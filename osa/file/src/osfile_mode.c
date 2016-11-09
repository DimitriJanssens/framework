#include "osfile.h"

static const char_t * _r = "r";
static const char_t * _rplus = "r+";
static const char_t * _w = "w";
static const char_t * _wplus = "w+";
static const char_t * _a = "a";
static const char_t * _aplus = "a+";

const char_t * osfile_mode_to_os(OsFileMode_e mode)
{
  const char_t * rc = NULL;

  switch (mode)
  {
    case OSFILEMODE_R:
      rc = _r;
      break;
    case OSFILEMODE_RPLUS:
      rc = _rplus;
      break;
    case OSFILEMODE_W:
      rc = _w;
      break;
    case OSFILEMODE_WPLUS:
      rc = _wplus;
      break;
    case OSFILEMODE_A:
      rc = _a;
      break;
    case OSFILEMODE_APLUS:
      rc = _aplus;
      break;

    default:
      break;
  }

  return rc;
}

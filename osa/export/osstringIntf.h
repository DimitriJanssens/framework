#ifndef OSSTRING_INTF_H
#define OSSTRING_INTF_H

#include <common/commontypes.h>

typedef struct
{
  /*!
   * \brief Writes at most size bytes (including the terminating null byte ('\0')) to str.
   */
  Status_e (*string_write)(char_t * str, size_t size, size_t * const written, const char_t * format, ...);
  size_t (*string_length)(const char_t * str);

} OsStringIntf_t;

OsStringIntf_t * getOsStringIntf(void);

#ifdef UNITTESTS
void setDefaultOsStringIntfForUnittests(void);
void resetDefaultOsStringIntfForUnittests(void);
#endif

#endif

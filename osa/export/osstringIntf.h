#ifndef OSSTRING_INTF_H
#define OSSTRING_INTF_H

#include <common/commontypes.h>

typedef struct
{
  /*!
   * \brief Compares strings s1 and s2. When n != 0, it compares the only first (at most) n bytes of s1 and s2.
   */
  Status_e (*string_cmp)(const char_t * const s1, const char_t * const s2, size_t n);

  /*!
   * \brief Writes at most size bytes (including the terminating null byte ('\0')) to str.
   */
  Status_e (*string_write)(char_t * str, size_t size, size_t * const written, const char_t * format, ...);

  /*!
   * \brief Scans items values from a string in a predetermined format.
   */
  Status_e (*string_scan)(const char_t * const str, size_t items, const char_t * format, ...);

  /*!
   * \brief Returns the length of the string (excluding the terminating null byte ('\0')).
   */
  size_t (*string_length)(const char_t * str);

} OsStringIntf_t;

OsStringIntf_t * getOsStringIntf(void);

#ifdef UNITTESTS
void setDefaultOsStringIntfForUnittests(void);
void resetDefaultOsStringIntfForUnittests(void);
#endif

#endif

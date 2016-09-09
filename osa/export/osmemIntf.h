#ifndef OSMEMINTF_H
#define OSMEMINTF_H

#include <common/commontypes.h>

typedef struct
{
  void *(*malloc)(size_t size);
  void (*free)(void *ptr);
  Status_e (*memset)(void *s, int c, size_t n);
  Status_e (*memcpy)(void *dest, const void *src, size_t n);
  Status_e (*memcmp)(const void *s1, const void *s2, size_t n);
} OsMemIntf_t;

OsMemIntf_t *getOsMemIntf(void);

#ifdef UNITTESTS
void setDefaultOsMemIntfForUnittests(void);
void resetDefaultOsMemIntfForUnittests(void);
#endif

#endif

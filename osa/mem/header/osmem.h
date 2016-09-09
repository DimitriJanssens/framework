#ifndef OSMEM_H
#define OSMEM_H

#include <osa/osmemIntf.h>

void *osmem_malloc(size_t size);
void osmem_free(void *ptr);
Status_e osmem_memset(void *s, int c, size_t n);
Status_e osmem_memcpy(void *dest, const void *src, size_t n);
Status_e osmem_memcmp(const void *s1, const void *s2, size_t n);

#endif

#ifndef OSSTRING_H
#define OSSTRING_H

#include <osa/osstringIntf.h>

Status_e osstring_write(char_t * str, size_t size, size_t * const written, const char_t * format, ...);
Status_e osstring_scan(const char_t * const str, size_t items, const char_t * format, ...);
size_t osstring_length(const char_t * str);

#endif

#ifndef OSFILE_H
#define OSFILE_H

#include <osa/osfileIntf.h>

Status_e osfile_open(OsFile_t ** file, const char_t * const path, OsFileMode_e mode);
size_t osfile_read(OsFile_t * const file, void * const data, size_t size, size_t nmemb, size_t nmemb_offset);
size_t osfile_write(OsFile_t * const file, const void * const data, size_t size, size_t nmemb);
Status_e osfile_close(OsFile_t * file);

const char_t * osfile_mode_to_os(OsFileMode_e mode);

#endif

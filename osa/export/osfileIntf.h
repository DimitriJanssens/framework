#ifndef OSFILEINTF_H
#define OSFILEINTF_H

#include <common/commontypes.h>

typedef struct OsFile OsFile_t;

typedef enum
{
  OSFILEMODE_UNKNOWN = 0,
  OSFILEMODE_R, /* Open text file for reading. The stream is positioned at the beginning of the file. */
  OSFILEMODE_RPLUS, /* Open for reading and writing. The stream is positioned at the beginning of the file. */
  OSFILEMODE_W, /* Truncate file to zero length or create text file for writing. The stream is positioned at the beginning of the file. */
  OSFILEMODE_WPLUS, /* Open for reading and writing. The file is created if it does not exist, otherwise it is truncated. The stream is positioned at the beginning of the file. */
  OSFILEMODE_A, /* Open for appending (writing at end of file). The file is created if it does not exist. The stream is positioned at the end of the file. */
  OSFILEMODE_APLUS, /* Open for reading and appending (writing at end of file). The file is created if it does not exist. The initial file position for reading is at the beginning of the file, but output is always appended to the end of the file. */
  OSFILEMODE_SIZE
} OsFileMode_e;

typedef struct
{
  Status_e (*file_open)(OsFile_t ** file, const char_t * const path, OsFileMode_e mode);

  /*!
   * \brief Reads nmemb elements of data, each size bytes long, from the file, storing them at the location given by ptr.
   */
  size_t (*file_read)(OsFile_t * const file, void * const data, size_t size, size_t nmemb, size_t nmemb_offset);

  /*!
   * \brief Writes nmemb elements of data, each size bytes long, to the file, obtaining them from the location given by ptr.
   */
  size_t (*file_write)(OsFile_t * const file, const void * const data, size_t size, size_t nmemb);

  Status_e (*file_close)(OsFile_t * file);
} OsFileIntf_t;

OsFileIntf_t * getOsFileIntf(void);

#ifdef UNITTESTS
void setDefaultOsFileIntfForUnittests(void);
void resetDefaultOsFileIntfForUnittests(void);
#endif

#endif

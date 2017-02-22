#include "osfile.h"

#include <logging/logging.h>
#include <osa/osmemIntf.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

struct OsFile
{
  FILE * osfile;
};

Status_e osfile_open(OsFile_t ** file, const char_t * const path, OsFileMode_e mode)
{
  Status_e rc = STATUS_FAILURE;

  if((file != NULL) && (path != NULL))
  {
    const char_t * osmode = osfile_mode_to_os(mode);
    if(osmode != NULL)
    {
      const OsMemIntf_t * const memi = getOsMemIntf();

      *file = (OsFile_t *) memi->malloc(sizeof(**file));
      if(*file != NULL)
      {
        (*file)->osfile = fopen(path, osmode);
        if((*file)->osfile != NULL)
        {
          rc = STATUS_SUCCESS;
        }
        else
        {
          const char_t * error = strerror(errno);
          ERROR("fopen: %s\n", error);
        }

        if(rc != STATUS_SUCCESS)
        {
          memi->free(*file);
          *file = NULL;
        }
      }
    }
  }

  return rc;
}

size_t osfile_size(OsFile_t * const file, size_t size)
{
  size_t rc = 0;

  if((file != NULL) && (size > 0))
  {
    if(file->osfile != NULL)
    {
      if(fseek(file->osfile, 0, SEEK_END) == 0)
      {
        rc = (ftell(file->osfile) / size);
      }
      else
      {
        const char_t * error = strerror(errno);
        ERROR("fseek: %s\n", error);
      }
    }
  }

  return rc;
}

size_t osfile_read(OsFile_t * const file, void * const data, size_t size, size_t nmemb, size_t nmemb_offset)
{
  size_t rc = 0;

  if((file != NULL) && (data != NULL) && (nmemb != 0))
  {
    if(file->osfile != NULL)
    {
      if(fseek(file->osfile, nmemb_offset * size, SEEK_SET) == 0)
      {
        rc = fread(data, size, nmemb, file->osfile);
      }
      else
      {
        const char_t * error = strerror(errno);
        ERROR("fseek: %s\n", error);
      }
    }
  }

  return rc;
}

size_t osfile_write(OsFile_t * const file, const void * const data, size_t size, size_t nmemb)
{
  size_t rc = 0;

  if((file != NULL) && (data != NULL) && (nmemb != 0))
  {
    if(file->osfile != NULL)
    {
      if(fseek(file->osfile, 0, SEEK_END) == 0)
      {
        rc = fwrite(data, size, nmemb, file->osfile);
      }
      else
      {
        const char_t * error = strerror(errno);
        ERROR("fseek: %s\n", error);
      }
    }
  }

  return rc;
}

Status_e osfile_close(OsFile_t * file)
{
  Status_e rc = STATUS_FAILURE;

  if(file != NULL)
  {
    Boolean_e allok = BOOLEAN_TRUE;
    if(file->osfile != NULL)
    {
      if(fclose(file->osfile) != 0)
      {
        allok = BOOLEAN_FALSE;
        const char_t * error = strerror(errno);
        ERROR("fopen: %s\n", error);
      }
    }

    if(allok == BOOLEAN_TRUE)
    {
      file->osfile = NULL;
      getOsMemIntf()->free(file);

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

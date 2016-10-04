#include "osmem.h"

#ifdef UNITTESTS
void setDefaultOsMemIntfForUnittests(void)
{
	OsMemIntf_t * memi = getOsMemIntf();
	memi->malloc = osmem_malloc;
	memi->free = osmem_free;
	memi->memset = osmem_memset;
	memi->memcpy = osmem_memcpy;
	memi->memcmp = osmem_memcmp;
}

void resetDefaultOsMemIntfForUnittests(void)
{
	OsMemIntf_t * memi = getOsMemIntf();
	memi->malloc = NULL;
	memi->free = NULL;
	memi->memset = NULL;
	memi->memcpy = NULL;
	memi->memcmp = NULL;
}
#endif

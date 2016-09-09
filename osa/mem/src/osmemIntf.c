#include <osa/osmemIntf.h>

#include "osmem.h"

static OsMemIntf_t intf = 
{
	#ifndef UNITTESTS
	.malloc = osmem_malloc,
	.free = osmem_free,
	.memset = osmem_memset,
	.memcpy = osmem_memcpy,
	.memcmp = osmem_memcmp,
	#else
	.malloc = NULL,
	.free = NULL,
	.memset = NULL,
	.memcpy = NULL,
	.memcmp = NULL,
	#endif
};

OsMemIntf_t *getOsMemIntf(void)
{
	return &intf;
}

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
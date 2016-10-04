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

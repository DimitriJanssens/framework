#include "test_osmem_tcases.h"

#include <osa/osmemIntf.h>

START_TEST(test_malloc_NULL)
	ck_assert(getOsMemIntf()->malloc(0) == NULL);
END_TEST

START_TEST(test_free_NULL)
	getOsMemIntf()->free(NULL);
END_TEST

START_TEST(test_memset_NULL)
	ck_assert(getOsMemIntf()->memset(NULL, 0, 0) == STATUS_FAILURE);
END_TEST

START_TEST(test_memcmp_NULL)
	ck_assert(getOsMemIntf()->memcmp(NULL, NULL, 0) == STATUS_FAILURE);
END_TEST

START_TEST(test_memcpy_NULL)
	ck_assert(getOsMemIntf()->memcpy(NULL, NULL, 0) == STATUS_FAILURE);
END_TEST

START_TEST(test_malloc_free)
	void * buffer = NULL;
	buffer = getOsMemIntf()->malloc(1024);
	ck_assert(buffer != NULL);

	getOsMemIntf()->free(buffer);
	buffer = NULL;
END_TEST

START_TEST(test_memset_memcmp)
	#define BUFFERSIZE 5
	void * buffer = getOsMemIntf()->malloc(BUFFERSIZE);
	ck_assert(getOsMemIntf()->memset(buffer, 'A', BUFFERSIZE) == STATUS_SUCCESS);

	uint8_t stack[BUFFERSIZE] = { 'A' };
	ck_assert(getOsMemIntf()->memcmp(stack, buffer, BUFFERSIZE) != STATUS_SUCCESS);

	ck_assert(getOsMemIntf()->memset(stack, 'A', BUFFERSIZE) == STATUS_SUCCESS);

	ck_assert(getOsMemIntf()->memcmp(stack, buffer, BUFFERSIZE) == STATUS_SUCCESS);

	getOsMemIntf()->free(buffer);
	buffer = NULL;
END_TEST

START_TEST(test_memset_memcpy_memcmp)
	#define BUFFERSIZE 5
	void * buffer = getOsMemIntf()->malloc(BUFFERSIZE);
	ck_assert(getOsMemIntf()->memset(buffer, 'A', BUFFERSIZE) == STATUS_SUCCESS);

	uint8_t stack[BUFFERSIZE] = { 0 };
	ck_assert(getOsMemIntf()->memcmp(stack, buffer, BUFFERSIZE) != STATUS_SUCCESS);

	ck_assert(getOsMemIntf()->memcpy(buffer, stack, BUFFERSIZE) == STATUS_SUCCESS);

	ck_assert(getOsMemIntf()->memcmp(stack, buffer, BUFFERSIZE) == STATUS_SUCCESS);

	getOsMemIntf()->free(buffer);
	buffer = NULL;
END_TEST

TCase *tcase_osmem(void)
{
	TCase *tc = tcase_create("TestCase OsMemIntf");
	tcase_set_timeout(tc, 10);
	tcase_add_valgrind_fixtures(tc);
	tcase_add_checked_fixture(tc, setDefaultOsMemIntfForUnittests, resetDefaultOsMemIntfForUnittests);

	tcase_add_test(tc, test_malloc_NULL);
	tcase_add_test(tc, test_free_NULL);
	tcase_add_test(tc, test_memset_NULL);
	tcase_add_test(tc, test_memcmp_NULL);
	tcase_add_test(tc, test_memcpy_NULL);

	tcase_add_test(tc, test_malloc_free);
	tcase_add_test(tc, test_memset_memcmp);
	tcase_add_test(tc, test_memset_memcpy_memcmp);

	return tc;
}
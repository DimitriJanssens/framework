#include "test_list_tcases.h"

#include "test_list_helper.h"

static void localDummyDestructor(void * data)
{
  ck_assert(data != NULL);
}

START_TEST(test_list_NULL)
  const ListIntf_t * const listi = getListIntf();

  List_t *list;
  ck_assert(listi->list_create(NULL, NULL) == STATUS_FAILURE);
  ck_assert(listi->list_create(NULL, localDummyDestructor) == STATUS_FAILURE);
  ck_assert(listi->list_create(&list, NULL) == STATUS_FAILURE);
  ck_assert(listi->list_size(NULL) == 0);
  ck_assert(listi->list_destroy(NULL) == STATUS_FAILURE);  
END_TEST

START_TEST(test_list_create_destroy)
  const ListIntf_t * const listi = getListIntf();

  List_t *list;
  ck_assert(listi->list_create(&list, localDummyDestructor) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 0);
  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

TCase * tcase_list_list(void)
{
  TCase *tc = tcase_create("TestCase List List");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_list_setup, test_list_teardown);

  tcase_add_test(tc, test_list_NULL);
  tcase_add_test(tc, test_list_create_destroy);

  return tc;
}
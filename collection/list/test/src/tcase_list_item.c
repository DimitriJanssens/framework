#include "test_list_tcases.h"

#include <osa/osmemIntf.h>

#include "test_list_helper.h"

START_TEST(test_item_NULL)
  const ListIntf_t * const listi = getListIntf();

  List_t *list = (List_t*) 0x12345;
  void * data = (void*)0x12345;
  ListItemMatcher_t matcher = (ListItemMatcher_t)0x12345;

  ck_assert(listi->item_prepend(NULL, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_prepend(list, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_prepend(NULL, data) == STATUS_FAILURE);

  ck_assert(listi->item_append(NULL, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_append(list, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_append(NULL, data) == STATUS_FAILURE);

  ck_assert(listi->item_lookup_index(NULL, 0) == NULL);

  ck_assert(listi->item_lookup_matching(NULL, NULL, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_lookup_matching(list, NULL, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_lookup_matching(NULL, matcher, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_lookup_matching(NULL, NULL, &list) == STATUS_FAILURE);
  
  ck_assert(listi->item_remove_matching(NULL, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_remove_matching(list, NULL) == STATUS_FAILURE);
  ck_assert(listi->item_remove_matching(NULL, matcher) == STATUS_FAILURE);
END_TEST

static void localDataDestructor(void * data)
{
  ck_assert(data != NULL);
  getOsMemIntf()->free(data);
}

START_TEST(test_item_prepend)
  const ListIntf_t * const listi = getListIntf();

  void * data;

  List_t *list;
  ck_assert(listi->list_create(&list, localDataDestructor) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 0);

  data = getOsMemIntf()->malloc(1024);
  ck_assert(listi->item_prepend(list, data) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 1);

  data = getOsMemIntf()->malloc(1024);
  ck_assert(listi->item_prepend(list, data) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 2);

  data = getOsMemIntf()->malloc(1024);
  ck_assert(listi->item_prepend(list, data) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 3);

  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

START_TEST(test_item_append)
  const ListIntf_t * const listi = getListIntf();

  void * data;

  List_t *list;
  ck_assert(listi->list_create(&list, localDataDestructor) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 0);

  data = getOsMemIntf()->malloc(1024);
  ck_assert(listi->item_append(list, data) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 1);

  data = getOsMemIntf()->malloc(1024);
  ck_assert(listi->item_append(list, data) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 2);

  data = getOsMemIntf()->malloc(1024);
  ck_assert(listi->item_append(list, data) == STATUS_SUCCESS);
  ck_assert(listi->list_size(list) == 3);

  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

#define TEST_ITEM_MATCH_COUNT  23
struct matchdata
{
  size_t count;
};

static void localfillmatchlist(List_t *list)
{
  const ListIntf_t * const listi = getListIntf();

  ck_assert(list != NULL);

  for(size_t i = 0; i < TEST_ITEM_MATCH_COUNT; i++)
  {
    struct matchdata * data = (struct matchdata *)getOsMemIntf()->malloc(sizeof(struct matchdata));
    ck_assert(data != NULL);
    data->count = i;
    ck_assert(listi->item_append(list, data) == STATUS_SUCCESS);
  }

  ck_assert(listi->list_size(list) == TEST_ITEM_MATCH_COUNT);
}

static Status_e localMatchAll(const void * const data)
{
  ck_assert(data != NULL);

  return STATUS_SUCCESS;
}

static Status_e localMatchEven(const void * const data)
{
  Status_e rc = STATUS_FAILURE;

  ck_assert(data != NULL);

  const struct matchdata * const impl = (const struct matchdata * const) data;
  if(impl->count%2 == 0)
  {
    rc = STATUS_SUCCESS;
  }

  return rc;
}

START_TEST(test_item_lookup_index)
  const ListIntf_t * const listi = getListIntf();

  List_t *list;
  ck_assert(listi->list_create(&list, localDataDestructor) == STATUS_SUCCESS);

  localfillmatchlist(list);

  struct matchdata * data;

  data = (struct matchdata *) listi->item_lookup_index(list, 0);
  ck_assert(data != NULL);
  ck_assert(data->count == 0);

  data = (struct matchdata *) listi->item_lookup_index(list, TEST_ITEM_MATCH_COUNT - 1);
  ck_assert(data != NULL);
  ck_assert(data->count == TEST_ITEM_MATCH_COUNT - 1);

  data = (struct matchdata *) listi->item_lookup_index(list, TEST_ITEM_MATCH_COUNT);
  ck_assert(data == NULL);

  ck_assert(listi->list_size(list) == TEST_ITEM_MATCH_COUNT);

  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

START_TEST(test_item_remove_index)
  const ListIntf_t * const listi = getListIntf();

  List_t *list;
  ck_assert(listi->list_create(&list, localDataDestructor) == STATUS_SUCCESS);

  localfillmatchlist(list);

  for(size_t size = listi->list_size(list); size > 0; size--)
  {
    ck_assert(listi->item_remove_index(list, size - 1) == STATUS_SUCCESS);
    ck_assert(listi->list_size(list) == (size - 1));
  }
  
  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

START_TEST(test_item_lookup_matching)
  const ListIntf_t * const listi = getListIntf();

  List_t *list;
  ck_assert(listi->list_create(&list, localDataDestructor) == STATUS_SUCCESS);

  localfillmatchlist(list);

  List_t *result;
  ck_assert(listi->item_lookup_matching(list, localMatchAll, &result) == STATUS_SUCCESS);

  ck_assert(listi->list_size(list) == TEST_ITEM_MATCH_COUNT);
  ck_assert(listi->list_size(result) == TEST_ITEM_MATCH_COUNT);

  ck_assert(listi->list_destroy(result) == STATUS_SUCCESS);
  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

START_TEST(test_item_lookup_matching_even)
  const ListIntf_t * const listi = getListIntf();

  List_t *list;
  ck_assert(listi->list_create(&list, localDataDestructor) == STATUS_SUCCESS);

  localfillmatchlist(list);

  List_t *result;
  ck_assert(listi->item_lookup_matching(list, localMatchEven, &result) == STATUS_SUCCESS);

  ck_assert(listi->list_size(list) == TEST_ITEM_MATCH_COUNT);
  ck_assert(listi->list_size(result) == (int)(TEST_ITEM_MATCH_COUNT/2) + 1);

  ck_assert(listi->list_destroy(result) == STATUS_SUCCESS);
  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

START_TEST(test_item_remove)
  const ListIntf_t * const listi = getListIntf();

  List_t *list;
  ck_assert(listi->list_create(&list, localDataDestructor) == STATUS_SUCCESS);

  localfillmatchlist(list);

  ck_assert(listi->item_remove_matching(list, localMatchAll) == STATUS_SUCCESS);

  ck_assert(listi->list_size(list) == 0);

  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

START_TEST(test_item_remove_even)
  const ListIntf_t * const listi = getListIntf();

  List_t *list;
  ck_assert(listi->list_create(&list, localDataDestructor) == STATUS_SUCCESS);

  localfillmatchlist(list);

  ck_assert(listi->item_remove_matching(list, localMatchEven) == STATUS_SUCCESS);

  ck_assert(listi->list_size(list) == (int)(TEST_ITEM_MATCH_COUNT/2));

  ck_assert(listi->list_destroy(list) == STATUS_SUCCESS);
END_TEST

TCase * tcase_list_item(void)
{
  TCase *tc = tcase_create("TestCase List Item");
  tcase_set_timeout(tc, 10);
  tcase_add_valgrind_fixtures(tc);
  tcase_add_checked_fixture(tc, test_list_setup, test_list_teardown);

  tcase_add_test(tc, test_item_NULL);
  tcase_add_test(tc, test_item_prepend);
  tcase_add_test(tc, test_item_append);
  tcase_add_test(tc, test_item_lookup_index);
  tcase_add_test(tc, test_item_remove_index);
  tcase_add_test(tc, test_item_lookup_matching);
  tcase_add_test(tc, test_item_lookup_matching_even);
  tcase_add_test(tc, test_item_remove);
  tcase_add_test(tc, test_item_remove_even);

  return tc;
}

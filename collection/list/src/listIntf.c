#include <collection/listIntf.h>

#include "list.h"

static ListIntf_t intf = {
  #ifndef UNITTESTS
  .list_create = list_list_create,
  .list_size = list_list_size,
  .list_destroy = list_list_destroy,

  .item_prepend = list_item_prepend,
  .item_append = list_item_append,
  .item_lookup_index = list_item_lookup_index,
  .item_remove_index = list_item_remove_index,
  .item_lookup_matching = list_item_lookup_matching,
  .item_remove_matching = list_item_remove_matching,
  #else
  .list_create = NULL,
  .list_size = NULL,
  .list_destroy = NULL,

  .item_prepend = NULL,
  .item_append = NULL,
  .item_lookup_index = NULL,
  .item_remove_index = NULL,
  .item_lookup_matching = NULL,
  .item_remove_matching = NULL,
  #endif
};

ListIntf_t * getListIntf(void)
{
  return &intf;
}

#ifdef UNITTESTS
void setDefaultListIntfForUnittests(void)
{
  ListIntf_t *intf = getListIntf();
  intf->list_create = list_list_create;
  intf->list_size = list_list_size;
  intf->list_destroy = list_list_destroy;

  intf->item_prepend = list_item_prepend;
  intf->item_append = list_item_append;
  intf->item_lookup_index = list_item_lookup_index;
  intf->item_remove_index = list_item_remove_index;
  intf->item_lookup_matching = list_item_lookup_matching;
  intf->item_remove_matching = list_item_remove_matching;
}

void resetDefaultListIntfForUnittests(void)
{
  ListIntf_t *intf = getListIntf();

  intf->list_create = NULL;
  intf->list_size = NULL;
  intf->list_destroy = NULL;

  intf->item_prepend = NULL;
  intf->item_append = NULL;
  intf->item_lookup_index = NULL;
  intf->item_remove_index = NULL;
  intf->item_lookup_matching = NULL;
  intf->item_remove_matching = NULL;
}
#endif
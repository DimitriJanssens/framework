#include "list.h"

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

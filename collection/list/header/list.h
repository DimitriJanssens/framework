#ifndef LIST_H
#define LIST_H

#include <collection/listIntf.h>

Status_e list_list_create(List_t ** list, ListItemDestructor_t destructor);
size_t list_list_size(List_t *list);
Status_e list_list_destroy(List_t *list);

Status_e list_item_destroy(List_t *list, ListItem_t *item);
Status_e list_item_prepend(List_t *list, void * data);
Status_e list_item_append(List_t *list, void * data);
void * list_item_lookup_index(List_t *list, size_t index);
Status_e list_item_remove_index(List_t *list, size_t index);
Status_e list_item_lookup_matching(List_t *list, ListItemMatcher_t matcher, List_t ** result);
Status_e list_item_remove_matching(List_t *list, ListItemMatcher_t matcher);

struct List
{
  ListItemDestructor_t destructor;
  ListItem_t *first;
};

struct ListItem
{
  ListItem_t *prev;
  void * data;
  ListItem_t *next;
};

#endif
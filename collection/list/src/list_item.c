#include "list.h"

#include <osa/osmemIntf.h>
#include <logging/logging.h>

static Status_e list_item_create(ListItem_t ** item, void * data)
{
  Status_e rc = STATUS_SUCCESS;

  if((item != NULL) && (data != NULL))
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    *item = (struct ListItem *) memi->malloc(sizeof(struct ListItem));
    if(*item != NULL)
    {
      (void) memi->memset(*item, 0, sizeof(struct ListItem));
      (*item)->data = data;

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e list_item_destroy(List_t *list, ListItem_t *item)
{
  Status_e rc = STATUS_FAILURE;

  if((list != NULL) && (item != NULL))
  {
    const OsMemIntf_t * const memi = getOsMemIntf();

    list->destructor(item->data);

    ListItem_t *prev = item->prev;
    ListItem_t *next = item->next;
    
    if(list->first == item)
    {
      list->first = next;
    }

    if(prev != NULL)
    {
      prev->next = next;
    }

    if(next != NULL)
    {
      next->prev = prev;
    }

    memi->free(item);

    rc = STATUS_SUCCESS;
  }

  return rc;
}

Status_e list_item_prepend(List_t *list, void * data)
{
  Status_e rc = STATUS_FAILURE;
  
  if((list != NULL) && (data != NULL))
  {
    ListItem_t *item;
    if(list_item_create(&item, data) == STATUS_SUCCESS)
    {
      item->prev = NULL;
      item->next = list->first;
      
      list->first = item;

      rc = STATUS_SUCCESS;
    }
    else
    {
      list->destructor(data);
    }
  }

  return rc;
}

Status_e list_item_append(List_t *list, void * data)
{
  Status_e rc = STATUS_FAILURE;
  
  if((list != NULL) && (data != NULL))
  {
    ListItem_t *item;
    if(list_item_create(&item, data) == STATUS_SUCCESS)
    {
      ListItem_t *last = list->first;
      if(last != NULL)
      {
        while(last->next != NULL)
        {
          last = last->next;
        }

        last->next = item;
        item->prev = last;
        item->next = NULL;

        rc = STATUS_SUCCESS;
      }
      else
      {
        list->first = item;
        item->prev = NULL;
        item->next = NULL;

        rc = STATUS_SUCCESS;
      }
    }
    else
    {
      list->destructor(data);
    }
  }

  return rc;
}

void * list_item_lookup_index(List_t *list, size_t index)
{
  void * rc = NULL;

  if(list != NULL)
  {
    if(index < list_list_size(list))
    {
      ListItem_t *item = list->first;
      while((item != NULL) && (index != 0))
      {
        item = item->next;
        index--;
      }

      if(item != NULL)
      {
        rc = item->data;
      }
    }
  }

  return rc;
}

Status_e list_item_remove_index(List_t *list, size_t index)
{
  Status_e rc = STATUS_FAILURE;

  if(list != NULL)
  {
    if(index < list_list_size(list))
    {
      ListItem_t *item = list->first;
      while((item != NULL) && (index != 0))
      {
        item = item->next;
        index--;
      }

      if(item != NULL)
      {
        rc = list_item_destroy(list, item);
      }
    }
  }

  return rc;
}

static void localDummyDataDestructor(void * data)
{
  (void) data;
  TRACE("LIST: executing dummy data destructor from lookup list\n");
}

Status_e list_item_lookup_matching(List_t *list, ListItemMatcher_t matcher, List_t ** result)
{
  Status_e rc = STATUS_FAILURE;

  if((list != NULL) && (matcher != NULL) && (result != NULL))
  {
    if(list_list_create(result, localDummyDataDestructor) == STATUS_SUCCESS)
    {
      ListItem_t *item = list->first;
      while(item != NULL)
      {
        if(matcher(item->data) == STATUS_SUCCESS)
        {
          (void) list_item_append(*result, item->data);
        }

        item = item->next;
      }

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

Status_e list_item_remove_matching(List_t *list, ListItemMatcher_t matcher)
{
  Status_e rc = STATUS_FAILURE;

  if((list != NULL) && (matcher != NULL))
  {
    {
      ListItem_t *item = list->first;
      while(item != NULL)
      {
        if(matcher(item->data) == STATUS_SUCCESS)
        {
          ListItem_t *tmpnext = item->next;
          (void) list_item_destroy(list, item);
          item = tmpnext;
        }
        else
        {
          item = item->next;
        }
      }

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}
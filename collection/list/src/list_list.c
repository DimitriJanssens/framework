#include "list.h"

#include <osa/osmemIntf.h>

Status_e list_list_create(List_t ** list, ListItemDestructor_t destructor)
{
  Status_e rc = STATUS_FAILURE;

  if((list != NULL) && (destructor != NULL))
  {
    const OsMemIntf_t * const memi = getOsMemIntf();
    List_t *newList = (struct List *)memi->malloc(sizeof(struct List));
    if(newList != NULL)
    {
      newList->destructor = destructor;
      newList->first = NULL;

      *list = newList;
      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}

size_t list_list_size(List_t *list)
{
  size_t rc = 0;

  if(list != NULL)
  {
    ListItem_t *item = list->first;
    while(item != NULL)
    {
      rc++;
      item = item->next;
    }
  }

  return rc;
}

Status_e list_list_destroy(List_t *list)
{
  Status_e rc = STATUS_FAILURE;

  if(list != NULL)
  {
    Boolean_e allOk = BOOLEAN_TRUE;
    ListItem_t *item = list->first;
    while((item != NULL) && (allOk == BOOLEAN_TRUE))
    {
     if(list_item_destroy(list, item) == STATUS_FAILURE)
     {
      allOk = BOOLEAN_FALSE;
     }

     item = list->first;
    }

    if(allOk == BOOLEAN_TRUE)
    {
      list->destructor = NULL;
      list->first = NULL;
      getOsMemIntf()->free(list);

      rc = STATUS_SUCCESS;
    }
  }

  return rc;
}


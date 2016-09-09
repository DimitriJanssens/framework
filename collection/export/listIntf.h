#ifndef LISTINTF_H
#define LISTINTF_H

#include <common/commontypes.h>

typedef struct List List_t;
typedef struct ListItem ListItem_t;

typedef void (*ListItemDestructor_t)(void * data);
typedef Status_e (*ListItemMatcher_t)(const void * const data);

/*!
 * \brief Interface definition
 *
 * In order to provide a generic interface, all item storage and retrieval gets handled with void pointers.
 * Memory management of items that are contained by the list, is handled by the list.
 */
typedef struct
{
  /*!
   * \brief Creates a new list
   *
   */
  Status_e (*list_create)(List_t ** list, ListItemDestructor_t destructor);
  
  /*!
   * \brief Returns the itemcount (size) of the list
   */  
  size_t (*list_size)(List_t *list);

  /*!
   * \brief Destroys the list
   *
   * All remaining items in the list are destroyed 
   */
  Status_e (*list_destroy)(List_t *list);

  /*!
   * \brief Prepends an item to the list
   */
  Status_e (*item_prepend)(List_t *list, void * data);

  /*!
   * \brief Appends an item to the list
   */
  Status_e (*item_append)(List_t *list, void * data);

  /*!
   * \brief Returns the item at the given index
   */
  void * (*item_lookup_index)(List_t *list, size_t index);

  /*!
   * \brief Destroys the item at the given index
   */
  Status_e (*item_remove_index)(List_t *list, size_t index);

  /*!
   * \brief Creates a new list containing all items that were matched using the given matcher function.
   */
  Status_e (*item_lookup_matching)(List_t *list, ListItemMatcher_t matcher, List_t ** result);

  /*!
   * \brief Destroys all items that were matched using the given matcher function.
   */
   Status_e (*item_remove_matching)(List_t *list, ListItemMatcher_t matcher);
} ListIntf_t;

ListIntf_t * getListIntf(void);

#ifdef UNITTESTS
void setDefaultListIntfForUnittests(void);
void resetDefaultListIntfForUnittests(void);
#endif

#endif
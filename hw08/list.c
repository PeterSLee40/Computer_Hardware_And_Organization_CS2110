/**
 * CS 2110 - Fall 2018 - Homework #8
 *
 * @author Peter Lee
 *
 * struct list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 0 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED_PARAMETER(x) (void)(x)

/* The struct list_node struct. Has a next pointer, and data. */
/* DO NOT MODIFY THIS STRUCTURE */
/* Only this file should deal with the struct list_node struct */
struct list_node
{
    struct list_node *next;
    struct person *data;
};

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked struct list. */
static inline struct list_node *create_node(struct person *data);

/** create_node
  *
  * Helper function that creates a struct list_node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in the struct list
  * @return a struct list_node
  */
static struct list_node* create_node(struct person *data)
{
  //create a new node, allocate memory for list_node
  struct list_node* node;
  node = (struct list_node *) malloc(sizeof(struct list_node));
  if (node == NULL) {
    return NULL;
  }
  node-> data = data;
  node->next = NULL;
  return node;
}

/** create_list
  *
  * Creates a struct list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head and tail to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new struct list or NULL on failure
  */
struct list *create_list(void)
{

  struct list *listAddr = (struct list *) malloc(sizeof(struct list));
  if (listAddr) {
    listAddr->size = 0;
    listAddr->head = NULL;
    listAddr->tail = NULL;
  }
    return listAddr;
}

/** copy_list
  *
  * Create a new struct list structure, new nodes, and new copies of the data
  * by using the person_copy function (check out the description for this in
  * person.c).
  *
  * If listToCopy is NULL return NULL. For memory allocations
  * failures, including if person_copy returns 0 (indicating a memory
  * allocation failure), your code must not leak memory. This means that if any
  * memory allocation failures occur, before you return NULL, you must go back
  * and free all data in the new struct list, nodes in the new struct list, and
  * the new struct list itself (you may find the empty_list function useful for
  * this).
  *
  * If you need to free a newly allocated person struct created by person_copy,
  * you should use person_free.
  *
  * @param listToCopy A pointer to the struct list structure to make a copy of
  * @return The struct list structure created by copying the old one, or NULL on
  *         failure (includes any of the parameters being null)
  */
struct list *copy_list(struct list *listToCopy)
{

  //make new list
  struct list *newlist = create_list();
  if (!listToCopy || !newlist) {
    free(newlist);
    return NULL;
  }
  struct list_node *current = listToCopy->head;
  //struct person **addr;
  
  while (current != NULL) {
    struct person **addr = NULL;
    if (person_copy(current->data, addr) == 0) {
      empty_list(newlist);
      person_free(addr);
      return NULL;
    }
    if (push_back(newlist, *addr) == 0) {
      person_free(addr);
      empty_list(newlist);
      free(newlist);
      return NULL;
    }
    current = current->next;
  }
  return newlist;
}

/** push_front
  *
  * Adds the element at the front of the struct list.
  *
  * @param listToPrependTo a pointer to the struct list structure.
  * @param data the data to add to the struct list.
  * @return 0 if the struct list is NULL, 1 if successful.
  */
int push_front(struct list *listToPrependTo, struct person *data)
{
  if (!listToPrependTo) {
    return 0;
  }
  struct list_node* newNode;
  struct list_node* tempFront;
  newNode = create_node(data);
  tempFront =  listToPrependTo->head;
  if (!tempFront) {
    listToPrependTo->head = newNode;
    listToPrependTo->tail = newNode;
    newNode->next = NULL;
    listToPrependTo->size++;
    return 1;
  } else {
    newNode->next = tempFront;
    listToPrependTo->head = newNode;
    listToPrependTo->size++;
    return 1;
  }
}

/** push_back
  *
  * Adds the element to the back of the struct list.
  *
  * @param listToAppendTo a pointer to the struct list structure.
  * @param data the data to add to the struct list.
  * @return 0 if the struct list is NULL, 1 if successful.
  */
int push_back(struct list *listToAppendTo, struct person *data)
{
  if (!listToAppendTo) {
    return 0;
  }
  struct list_node* newNode;
  newNode = create_node(data);
  if (!newNode) {
    return 0;
  }
  if (!listToAppendTo->head) {
    listToAppendTo->head = newNode;
    listToAppendTo->tail = newNode;
  } else {
    listToAppendTo->tail->next = newNode;
    listToAppendTo->tail = newNode;
    
  }
  listToAppendTo->size++;
  return 1;
}

/** add
  *
  * Add the element at the specified index in the struct list. This index must lie in
  * the inclusive range [0,size].
  * For example, if you have no elements in the struct list,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the struct list,
  * you should be able to add to index 2 but no further.
  *
  * @param listToAddTo a pointer to the struct list structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the struct list
  * @return 0 if the index is out of bounds or the struct list is NULL
  *         (do not add the data in this case)
  *         otherwise return 1
  */
int add(struct list *listToAddTo, int index, struct person *data)
{
  if (!listToAddTo) {
    return 0;
  } else if ((index > listToAddTo->size) ||  index < 0) {
    return 0;
  } else if (index == 0) {
    return push_front(listToAddTo, data);
  } else if (index == (listToAddTo->size)) {
    return push_back(listToAddTo, data);
  }
  struct list_node* newNode = create_node(data);
  struct list_node* currentNode = listToAddTo->head;
  struct list_node* prevNode;
  for (int i = 0; i < index; i++) {
    prevNode = currentNode;
    currentNode = currentNode->next;
  }
  prevNode->next = newNode;
  newNode->next = currentNode;
  listToAddTo->size++;
  return 1;
}

/** front
  *
  * Gets the data at the front of the struct list
  * If the struct list is empty or the struct list is NULL, return 0.
  *
  * @param listToGetFrontOf a pointer to the struct list
  * @param dataOut A pointer to a pointer used to return the data at the first
  *                struct list_node in the struct list or NULL on failure.
  * @return 0 if dataOut is NULL or the struct list is NULL or empty, 1 if
  *         successful.
  */
int front(struct list *listToGetFrontOf, struct person **dataOut)
{ 
  if (!listToGetFrontOf || !dataOut) {
    return 0;
  } else if (listToGetFrontOf->size == 0 || !listToGetFrontOf->head) {
    *dataOut = NULL;
    return 0;
  }
    *dataOut = listToGetFrontOf->head->data;
    return 1;
}

/** back
  *
  * Gets the data at the back of the struct list
  * If the struct list is empty or the struct list is NULL, return 0.
  *
  * @param listToGetBackOf a pointer to the struct list
  * @param dataOut A pointer to a pointer used to return the data at the last
  *                struct list_node in the struct list or NULL on failure.
  * @return 0 if dataOut is NULL or the struct list is NULL or empty, 1
  *         otherwise
  */
int back(struct list *listToGetBackOf, struct person **dataOut)
{
  if (!listToGetBackOf || !dataOut) {
    return 0;
  } else if (listToGetBackOf->size == 0 || !dataOut || !listToGetBackOf->tail) {
    *dataOut = NULL;
    return 0;
  }
    *dataOut = listToGetBackOf->tail->data;
    return 1;
}

/** get
  *
  * Gets the data at the specified index in the struct list
  *
  * @param listToGetDataFrom a pointer to the struct list structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *        specified index in the struct list or NULL on failure.
  * @return 0 if dataOut is NULL or index is out of range of the struct list or
  *         the struct list is NULL, 1 otherwise
  */
int get(struct list *listToGetDataFrom, int index, struct person **dataOut)
{
  if (!listToGetDataFrom) {
    *dataOut = NULL;
    return 0;
  } else if (index < 0 || index > (listToGetDataFrom->size - 1)) {
    *dataOut = NULL;
    return 0;
  }
  if (!dataOut) {
    return 0;
  }
  struct list_node *current = listToGetDataFrom->head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  *dataOut = current->data;
  return 1;
}

/** size
  *
  * Gets the size of the struct list
  *
  * if the struct list is NULL, return 0.
  *
  * @param listToGetSizeOf a pointer to the struct list structure
  * @param A pointer used to return the size of the struct list, set to -1 on NULL struct list
  * @return 0 if sizeOut is NULL or struct list is NULL, 1 otherwise
  */
int size(struct list *listToGetSizeOf, int *sizeOut)
{
  if (!listToGetSizeOf) {
    *sizeOut = -1;
    return 0;
  }
  
  if (!sizeOut) {
    return 0;
  }
  *sizeOut = listToGetSizeOf->size;
  return 1;
}

/** contains
  *
  * Traverses the struct list, trying to see if the struct list contains some
  * data.
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * comparator (person_eq_name in this case) says is equal.
  *
  * If there are multiple pieces of data in the struct list which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  * Use person_eq_name to compare person structs. Be sure to take a look at that
  * function before you use it! Also be sure not to use person_eq.
  *
  * @param listToSearch a pointer to the struct list structure
  * @param data The data, to see if it exists in the struct list
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the struct list or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(struct list *listToSearch, struct person *data, struct person **dataOut)
{
  if (!dataOut) {
    return 0;
  }
  if (!listToSearch || !data) {
    *dataOut = NULL;
    return 0;
  } if (!(listToSearch->head) || listToSearch->size == 0) {
    *dataOut = NULL;
    return 0;
  }
  struct list_node *current = listToSearch->head;
  for (int i = 0; i < listToSearch->size; i++) {
    if (person_eq_name(current->data, data) == 0) {
      *dataOut = current->data;
      return 1;
    }
    current = current->next;
  }
  *dataOut = NULL;
  return 0;
}


/** pop_front
  *
  * Removes the struct list_node at the front of the struct list, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the struct list.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                struct list_node or NULL on failure
  * @return 0 if dataOut is NULL or the struct list is NULL or empty, else 1
  */
int pop_front(struct list *listToPopFrom, struct person **dataOut)
{
  if (!listToPopFrom) {
    *dataOut = NULL;
    return 0;
  } else if (!dataOut) {
    return 0;
  } 
  if (listToPopFrom->size == 0) {
    *dataOut = NULL;
    return 0;
  }
  struct list_node *front = listToPopFrom->head;
  if (!front || !(front->data)) {
    *dataOut = NULL;
    return 0;
  } else {
    if (listToPopFrom->size == 1) {
      listToPopFrom->tail = NULL;
    }
    struct list_node *nextHead = front->next;
    listToPopFrom->head = nextHead;
    *dataOut = front->data;
    //person_free(front->data);
    free(front);
    listToPopFrom->size--;
    return 1;
  }
}

/** pop_back
  *
  * Removes the struct list_node at the back of the struct list, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the struct list.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                struct list_node or NULL on failure
  * @return 0 if dataOut is NULL or the struct list is NULL or empty, else 1
  */
int pop_back(struct list *listToPopFrom, struct person **dataOut)
{
  if (!listToPopFrom) {
    *dataOut = NULL;
    return 0;
  }
  if (!dataOut) {
    return 0;
  }
  if (listToPopFrom->size == 0) {
    *dataOut = NULL;
    return 0;
  }
  struct list_node *back = listToPopFrom->tail;
  if (back == NULL) {
    return 0;
  } else {
      struct list_node *prev = listToPopFrom->head;
      if (listToPopFrom->size == 1) {
        listToPopFrom->head = NULL;
      }
      for (int i = 0; i < (listToPopFrom->size - 2); i++) {
        prev = prev->next;
      }
      prev->next = NULL;
      listToPopFrom->tail = prev;
      *dataOut = back->data;
      free(back);
      listToPopFrom->size--;
      return 1;
  }
}

/** list_remove
  *
  * Removes a specified data element from the struct list.
  *
  * The element to be removed is the one that is equal to the data_to_remove
  * parameter by way of the comparator function passed in. This function
  * returns 0 when its arguments are equal.
  *
  * If the struct list contains multiple elements that are equal to data_to_remove,
  * then the one with the lowest index only is to be removed.
  *
  * Use person_eq_name to compare person structs. Be sure to take a look at that
  * function before you use it! Also be sure not to use person_eq.
  *
  * @param listToRemoveFrom             a pointer to the struct list structure
  * @param data_to_remove               The element to remove from the struct list.
  * @param dataOut                      A pointer to a pointer used to
  *                                     return the data from the specified
  *                                     index in the struct list or NULL on failure
  *
  * @return int                         0 if dataOut is NULL, or the list is
  *                                     NULL, else 1.
  */
int list_remove(struct list *listToRemoveFrom,
                 struct person *data_to_remove,
                 struct person **dataOut)
{
  if (!listToRemoveFrom) {
    *dataOut = NULL;
    return 0;
  } else if (!dataOut) {
    return 0;
  } else if (listToRemoveFrom->size == 0) {
    return 0;
  }
  if (!contains(listToRemoveFrom,data_to_remove,dataOut)) {
    *dataOut = NULL;
    return 0;
  }
  if (!person_eq_name(listToRemoveFrom->head->data, data_to_remove)) {
    return pop_front(listToRemoveFrom, dataOut);
  }

  struct list_node *current = listToRemoveFrom->head;
  for (int i = 0; i < (listToRemoveFrom->size); i++) {
    if (!person_eq_name(current->next->data, data_to_remove)) {
      *dataOut = current->next->data;
      if (current->next == listToRemoveFrom->tail) {
        listToRemoveFrom->tail = current;
      }
      struct list_node *removed = current->next;
      current->next = current->next->next;
      listToRemoveFrom->size--;
      free(removed);
      return 1;
    }
    current = current->next;
  }
  return 0;
}

/** empty_list
  *
  * Empties the struct list. After this is called, the struct list should be
  * empty. This does not free the struct list struct itself, just all nodes and
  * data within. Make sure to check that listToEmpty and is not NULL before
  * using it.
  *
  * Call person_free to free a person struct.
  *
  * @param listToEmpty a pointer to the struct list structure
  */
void empty_list(struct list *listToEmpty)
{
  if (!listToEmpty) {
    return;
  } else if (!(listToEmpty->size)) {
    return;
  } else {
    struct list_node *front = listToEmpty->head;
    while(listToEmpty->head) {
      front = listToEmpty->head;
      if (listToEmpty->size == 1) {
        listToEmpty->tail = NULL;
      }
      struct list_node *nextHead = front->next;
      listToEmpty->head = nextHead;
      person_free(front->data);
      free(front);
      listToEmpty->size--;
    }
  }
}

/** reverse
  *
  * Reverses the singly linked struct list in place.
  *
  * @param listToReverse to append to.
  * @return 1 if the operation was a success, 0 otherwise (listToReverse
  *         was NULL)
  */
int reverse(struct list *listToReverse)
{
  //i want to flip all the pointers, so maybe do a for loop,
  //for (c = 0; c < n/2; c++) {
  //  t          = array[c];
  //  array[c]   = array[end];
  //  array[end] = t;
  //  end--;
  if (!listToReverse) {
    return 0;
  } else if (listToReverse->size == 0) {
    return 1;
  }
  else {
    struct list_node *prev   = NULL; 
    struct list_node *current = listToReverse->head; 
    struct list_node *oldhead = listToReverse->head; 
    struct list_node *next = NULL; 
    while (current != NULL) 
    { 
        // Store next 
        next  = current->next;  // Reverse current node's pointer 
        current->next = prev;   // Move pointers one position ahead. 
        prev = current; 
        current = next; 
    } 
    listToReverse->head = prev; 
    listToReverse->tail = oldhead;
    return 1;
  }
  return 0;
}

/** concat
  *
  * Concatinates firstList and secondList. This function should append
  * secondList to the end of firstList.
  *
  * NOTE: this function will effectively empty lastList onto firstList which
  *       means that lastList will be empty (head == tail == NULL and size == 0)
  *       at the end of the function and firstList will contain all the elements
  *       from both lists. Be sure to update the size, head, and tail pointers
  *       accordingly.
  *
  * example: if firstList is a->b->c and second struct list is d->e->f
  * after the function call, firstList will be a->b->c->d->e->f and
  * secondList will be empty.
  *
  *
  * @param firstList to append to.
  * @param secondList the struct list to append to firstList
  * @return 1 if the operation was a success, 0 otherwise (firstList or
  *         secondList is null)
  */
int concat(struct list *firstList, struct list *lastList)
{
    if (!firstList || !lastList) {
      return 0;
    }
    
    if (firstList->size == 0) {
      firstList->head = lastList->head;
      firstList->tail = lastList->tail;
      firstList->size = firstList->size + lastList->size;
      lastList->size = 0;
      lastList->head = NULL;
      lastList->tail = NULL;
      //sempty_list(lastList);
      return 1;
    }

    if (lastList->size > 0) {
      firstList->size = firstList->size + lastList->size;
      firstList->tail->next = lastList->head;
      firstList->tail = lastList->tail;
      lastList->size = 0;
      lastList->head = NULL;
      lastList->tail = NULL;
    }
    return 1;
}

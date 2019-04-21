//
// Created by wangrl on 19-4-21.
//

#include <stdlib.h>
#include <stdio.h>

// Singly linked lists
typedef struct NODE {
    struct NODE *link;
    int         value;
} Node;

/**
 * Insert into an ordered, single linked list. The argument are a
 * pointer to the first node in the list, and the value to insert.
 */
int sll_insert(Node *current, int new_value) {
    Node *previous;
    Node *new;

    /**
     * Look for hte right place by walking down the list
     * until we reach a node whose value is greater than
     * or equal to the new value.
     */
    while (current->value < new_value) {
        previous = current;
        current = current->link;
    }

    /**
     * Allocate a new node and store the new value into it.
     * In this event, we return FALSE.
     */
    new = (Node *)malloc(sizeof(Node));
    if (new == NULL)
        return 0;

    new->value = new_value;

    /**
     * Insert the new node into the list, and return TRUE.
     */
    new->link = current;
    previous->link = new;

    return 1;
}

// 上述函数存在bug,会碰到previous为空或者current为空的情况。

/**
 * In order to add a node to the beginning of the list, the function must change the
 * root pointer.
 * 修改指针的指向，那么需要传递双重指针，因为单级指针只会修改指向的值，不会修改指向。
 * The better solution is to pass a pointer to root as an argument.
 */
#define FALSE 0
#define TRUE 1

int sll_insert_p(Node **rootp, int new_value) {
    Node *current;
    Node *previous;
    Node *new;

    /**
     * Get the pointer to the first node.
     */
    current = *rootp;
    previous = NULL;

    /**
     * Look for the right place by walking down the list
     * until we reach a node whose value is great than or equal
     * to the new value.
     */
   while (current != NULL && current->value < new_value) {
       previous = current;
       current = current->link;
   }

   /**
    * Allocate a new node and store the new value into it.
    * In this event, we return FALSE.
    */
  new = (Node *)malloc(sizeof(Node));
  if (new == NULL)
      return FALSE;

  new->value = new_value;

  /**
   * Insert the new node into the list, and return TRUE.
   */
  new->link = current;
  if (previous == NULL)
      *rootp = new;
  else
      previous->link = new;

  return TRUE;
}

int main(int argc, char *argv[]) {



}


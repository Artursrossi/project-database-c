/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef DOUBLY_LINKED_h
#define DOUBLY_LINKED_h

#include <stdbool.h>
#include <stdint.h>

/* Constants */
struct DL_Node {
  int32_t data;
  struct DL_Node *next;
  struct DL_Node *prev;
};
typedef struct DL_Node dl_node_t;

/* Functions prototypes */

/**
 * @brief Free up the space allocated by the Nodes
*/
void doubly_linked_destroy();

/**
 * @brief Insert value to the doubly linked list (ordering by ascending)
 * 
 * @param data Value to be added
*/
void doubly_linked_insert(int32_t data);

/**
 * @brief Remove element by value
 * 
 * @param data Value to be removed
 * 
 * @return True for removed, False for not found
*/
bool doubly_linked_remove(int32_t data);

/**
 * @brief Execute a function for each data of doubly linked list (for generic iteration)
 * 
 * @param iteration_fnc Pointer to a generic function that will receive each data of doubly linked list
*/
void doubly_linked_iteration(void (*iteration_fnc)(int32_t));

/**
 * @brief Returns the number of elements in doubly linked list
 * 
 * @return Number of elements in doubly linked list
*/
int32_t doubly_linked_length();

/**
 * @brief Reverse doubly linked list
 * 
 * @example
 *  HEAD -> 1 <-> 2 <-> 3 <-> 4 <-> 5 -> NULL
 *  NULL <- 1 <-> 2 <-> 3 <-> 4 <-> 5 <- HEAD
 * 
*/
void doubly_linked_reverse();

#endif // DOUBLY_LINKED_H

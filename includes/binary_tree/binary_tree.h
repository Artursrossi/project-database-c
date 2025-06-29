/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>
#include <stdint.h>

#include "../../src/database.h"

/* Constants */
struct BT_Node_Data{
  char document[DOCUMENT_LENGTH];
  int32_t index;
};
typedef struct BT_Node_Data bt_node_data_t;
struct BT_Node {
  bt_node_data_t data;
  struct BT_Node *left;
  struct BT_Node *right;
};
typedef struct BT_Node bt_node_t;

/* Functions prototypes */

/**
 * @brief Free all nodes and release memory used by the binary tree
*/
void binary_tree_destroy();

/**
 * @brief Insert a new value into the binary tree
 * 
 * @param data Value to be inserted into the tree
 * 
 * @return true if the value was successfully inserted, false if the value already exists (duplicate)
*/
bool binary_tree_insert(bt_node_data_t data);

/**
 * @brief Search for a value in the binary tree
 * 
 * @param value Value to be searched in the tree
 * 
 * @return true if the value exists in the tree, false otherwise
*/
bool binary_tree_search(char *document, bt_node_data_t *searched_value);

/**
 * @brief Remove a value from the binary tree
 * 
 * @param data Value to be removed from the tree
 * 
 * @return true if the value was found and removed, false if not found
*/
bool binary_tree_remove(char *document);

#endif // BINARY_TREE_H

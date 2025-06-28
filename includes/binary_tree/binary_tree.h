/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>
#include <stdint.h>

/* Constants */
struct BT_Node {
  int32_t data;
  struct BT_Node *left;
  struct BT_Node *right;
};
typedef struct BT_Node bt_node_t;

typedef void (*bt_inorder_fnc_t)(int32_t data);
typedef void (*bt_reverse_inorder_fnc_t)(int32_t data, int32_t level);

/* Functions prototypes */

/**
 * @brief Free all nodes and release memory used by the binary tree
*/
void binary_tree_destroy();

/**
 * @brief Returns the total number of nodes in the binary tree
 * 
 * @return Number of nodes currently stored in the binary tree
*/
int32_t binary_tree_length();

/**
 * @brief Returns the height (max depth) of the binary tree
 * 
 * @return Height of the binary tree
 */
int32_t binary_tree_height();

/**
 * @brief Insert a new value into the binary tree
 * 
 * @param data Value to be inserted into the tree
 * 
 * @return true if the value was successfully inserted, false if the value already exists (duplicate)
*/
bool binary_tree_insert(int32_t data);

/**
 * @brief Search for a value in the binary tree
 * 
 * @param value Value to be searched in the tree
 * 
 * @return true if the value exists in the tree, false otherwise
*/
bool binary_tree_search(int32_t data);

/**
 * @brief Remove a value from the binary tree
 * 
 * @param data Value to be removed from the tree
 * 
 * @return true if the value was found and removed, false if not found
*/
bool binary_tree_remove(int32_t data);

/**
 * @brief Traverse and iterate the binary tree in inorder (Left, Node, Right)
 * 
 * @param cb Callback function that receives the Node data
 */
void binary_tree_inorder_iteration(bt_inorder_fnc_t cb);

/**
 * @brief Traverse and iterate the binary tree in reverse inorder (Right, Node, Left)
 * 
 * @param cb Callback function that receives the Node data
 */
void binary_tree_reverse_inorder_iteration(bt_reverse_inorder_fnc_t cb);

#endif // BINARY_TREE_H

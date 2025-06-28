/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"

/* Variables */
static bt_node_t *root = NULL;
static int32_t length = 0;

static void recursive_destroy(bt_node_t *node){
  if(node == NULL) return;

  /* Go deepest on left, destroying all nodes recursively */
  if(node->left != NULL){
    recursive_destroy(node->left);

    /* Free up memory space for the node */
    free(node->left);
    node->left = NULL;
  }

  /* Go deepest on right, destroying all nodes recursively */
  if(node->right != NULL){
    recursive_destroy(node->right);

    /* Free up memory space for the node */
    free(node->right);
    node->right = NULL;
  }

  return;
}

void binary_tree_destroy(){
  if(root == NULL) return;

  /* Free up memory space for all childrens of root, recursively */
  recursive_destroy(root);

  /* Free up memory space for root, and reset local variables */
  free(root);
  root = NULL;
  length = 0;

  return;
}

int32_t binary_tree_length(){
  return length;
}

int32_t recursive_height(bt_node_t *node) {
  if (node == NULL) return 0;

  /* Go deepest on the left and right side */
  int32_t left_height = recursive_height(node->left);
  int32_t right_height = recursive_height(node->right);

  /* Get biggest height (comparison between left and right sides) */
  int32_t biggest_height = left_height > right_height ? left_height : right_height;

  return biggest_height + 1; // Tree level starts at 1
}

int32_t binary_tree_height() {
  if (root == NULL) return 0;

  return recursive_height(root);
}

static bt_node_t * create_node(int32_t data){
  /* Allocate memory space (in BYTES) for a Node of binary tree */
  bt_node_t *node = (bt_node_t *) malloc(sizeof(bt_node_t));
  if(node == NULL){
    perror("A memory allocation error has occurred. (binary_tree.c) \n");
    exit(EXIT_FAILURE);
  }

  node->data = data;
  node->left = NULL;
  node->right = NULL;

  return node;
}

static void recursive_insert(bt_node_t *node, bt_node_t *new_node){
  if(new_node == NULL) return;
  
  if(new_node->data > node->data){
    /* Insert new node on right */
    if(node->right == NULL){
      node->right = new_node;
      return;
    }
    
    /* Go deepest on right */
    return recursive_insert(node->right, new_node);
  }
  
  if(new_node->data <= node->data){
    /* Insert new node on left */
    if(node->left == NULL) {
      node->left = new_node;
      return;
    }

    /* Go deepest on left */
    return recursive_insert(node->left, new_node);
  }
}

bool binary_tree_insert(int32_t data){
  /* Prevent duplicated value */
  bool is_duplicated = binary_tree_search(data);
  if(is_duplicated) return false;

  /* Create new node */
  bt_node_t *new_node = create_node(data);
  length++;

  /* Insert on the root */
  if(root == NULL){
    root = new_node;
    return true;
  }

  recursive_insert(root, new_node);

  return true;
}

static bt_node_t * recursive_search(bt_node_t *node, int32_t data){
  /* Item found, return node */
  if(data == node->data) return node;

  if(data > node->data){
    /* Data not found on right */
    if(node->right == NULL) return NULL;

    /* Search deepest on right */
    return recursive_search(node->right, data);
  }

  if(data <= node->data){
    /* Data not found on left */
    if(node->left == NULL) return NULL;

    /* Search deepest on left */
    return recursive_search(node->left, data);
  }

  return NULL;
}

bool binary_tree_search(int32_t data){
  if(root == NULL) return false;

  bt_node_t *node = recursive_search(root, data);
  if(node == NULL) return false;
  
  return true;
}

static bt_node_t * get_sucessor(bt_node_t *node){
  if(node == NULL || node->right == NULL) return NULL;

  /* Get sucessor of received node value by:
      1. Go one time right (to get a higher value than received node value)
      2. Go left n times as possible (get lowest value, but bigger than received node value, therefore, the sucessor)
    Visual representation:
        50              - Received node (50)
    40      60          - Go right (60)
          55  70        - Go left (55)
        52              - Go left (52)
  */
  bt_node_t *deepest_node = node->right;
  while(deepest_node->left != NULL) deepest_node = deepest_node->left;

  return deepest_node;
}

static bt_node_t * recursive_remove(bt_node_t *node, int32_t data){
  if(node == NULL) return NULL;

  /* Go deepest on left and right sides, if the value does not match */
  if (node->data > data) {
    node->left = recursive_remove(node->left, data);
    return node;
  }
  if (node->data < data) {
    node->right = recursive_remove(node->right, data);
    return node;
  }

  /* Remove leaf Node */
  if(node->left == NULL && node->right == NULL){
    free(node);
    return NULL;
  }

  /* Remove Node with only right child */
  if(node->left == NULL){
    bt_node_t *temp = node->right; // Store memory address to a temp variable because of the return statement after free() function
    free(node);
    return temp;
  }

  /* Remove Node with only right child */
  if(node->right == NULL){
    bt_node_t *temp = node->left; // Store memory address to a temp variable because of the return statement after free() function
    free(node);
    return temp;
  }

  /* Remove Node with both childs */
  bt_node_t *sucessor = get_sucessor(node);
  if(sucessor != NULL){
    node->data = sucessor->data;
    node->right = recursive_remove(node->right, sucessor->data);
  }

  return node;
}

bool binary_tree_remove(int32_t data){
  if(root == NULL) return false;

  /* Verify if value exists, and do not remove if does not exist */
  bool is_founded = binary_tree_search(data);
  if(is_founded == false) return false;

  /* Delete node recursively */
  root = recursive_remove(root, data);
  length--;

  return true;
}

static void recursive_inorder(bt_node_t *node, bt_inorder_fnc_t cb) {
  if(node == NULL) return;

  /* Inorder order:
    1. Left
    2. Node
    3. Right
  */
  recursive_inorder(node->left, cb);
  cb(node->data);
  recursive_inorder(node->right, cb);

  return;
}

void binary_tree_inorder_iteration(bt_inorder_fnc_t cb){
  if(root == NULL) return;

  return recursive_inorder(root, cb);
}

static void recursive_reverse_inorder(bt_node_t *node, int32_t level, bt_reverse_inorder_fnc_t cb) {
  if (node == NULL) return;

  /* Reverse inorder order:
    1. Right
    2. Node
    3. Left
  */
  recursive_reverse_inorder(node->right, level + 1, cb);
  cb(node->data, level);
  recursive_reverse_inorder(node->left, level + 1, cb);

  return;
}


void binary_tree_reverse_inorder_iteration(bt_reverse_inorder_fnc_t cb){
  if(root == NULL) return;

  return recursive_reverse_inorder(root, 0, cb);
}
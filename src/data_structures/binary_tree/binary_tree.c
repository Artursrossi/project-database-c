/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"

/* Variables */
static bt_node_t *root = NULL;

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

  return;
}

static bt_node_t * create_node(bt_node_data_t data){
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
  
  if(strcmp(new_node->data.document, node->data.document) > 0){
    /* Insert new node on right */
    if(node->right == NULL){
      node->right = new_node;
      return;
    }
    
    /* Go deepest on right */
    return recursive_insert(node->right, new_node);
  }
  
  if(strcmp(new_node->data.document, node->data.document) <= 0){
    /* Insert new node on left */
    if(node->left == NULL) {
      node->left = new_node;
      return;
    }

    /* Go deepest on left */
    return recursive_insert(node->left, new_node);
  }
}

bool binary_tree_insert(bt_node_data_t data){
  /* Prevent duplicated value */
  bool is_duplicated = binary_tree_search(data.document, NULL);
  if(is_duplicated) return false;

  /* Create new node */
  bt_node_t *new_node = create_node(data);

  /* Insert on the root */
  if(root == NULL){
    root = new_node;
    return true;
  }

  recursive_insert(root, new_node);

  return true;
}

static bt_node_t * recursive_search(bt_node_t *node, char *document){
  /* Item found, return node */
  if(strcmp(document, node->data.document) == 0) return node;

  if(strcmp(document, node->data.document) > 0){
    /* Data not found on right */
    if(node->right == NULL) return NULL;

    /* Search deepest on right */
    return recursive_search(node->right, document);
  }

  if(strcmp(document, node->data.document) < 0){
    /* Data not found on left */
    if(node->left == NULL) return NULL;

    /* Search deepest on left */
    return recursive_search(node->left, document);
  }

  return NULL;
}

bool binary_tree_search(char *document, bt_node_data_t *searched_value){
  if(root == NULL) return false;

  bt_node_t *node = recursive_search(root, document);
  if(node == NULL) return false;
  
  if(searched_value != NULL){
    *searched_value = node->data;
  }
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

static bt_node_t * recursive_remove(bt_node_t *node, char *document){
  if(node == NULL) return NULL;

  /* Go deepest on left and right sides, if the value does not match */
  if (strcmp(node->data.document, document) > 0) {
    node->left = recursive_remove(node->left, document);
    return node;
  }
  if (strcmp(node->data.document, document) < 0) {
    node->right = recursive_remove(node->right, document);
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
    node->right = recursive_remove(node->right, sucessor->data.document);
  }

  return node;
}

bool binary_tree_remove(char *document){
  if(root == NULL) return false;

  /* Verify if value exists, and do not remove if does not exist */
  bool is_founded = binary_tree_search(document, NULL);
  if(is_founded == false) return false;

  /* Delete node recursively */
  root = recursive_remove(root, document);

  return true;
}
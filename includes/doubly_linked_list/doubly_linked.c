/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked.h"

/* Variables */
static dl_node_t *head = NULL;
static int32_t length = 0;

/* Free up memory space for each Node of doubly linked list, using recursively function for preventing memory leak */
static void recursive_free(dl_node_t *node){
  if (node->next != NULL) recursive_free(node->next);
  
  /* Free up memory space for each Node */
  free(node);
}

void doubly_linked_destroy(){
  if(head == NULL) return;

  recursive_free(head);
  head = NULL;
}

static dl_node_t * create_node(int32_t data){
  /* Allocate memory space (in BYTES) for a Node of doubly linked list */
  dl_node_t *node = (dl_node_t *) malloc(sizeof(dl_node_t));
  if(node == NULL){
    perror("A memory allocation error has occurred. (doubly_linked.c) \n");
    exit(EXIT_FAILURE);
  }

  node->data = data;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

void doubly_linked_insert(int32_t data){
  dl_node_t *new_node = create_node(data);
  length++;

  /* First element of doubly linked list */
  if(head == NULL){
    head = new_node;
    return;
  }

  /* If new node is lower than first element, then put it on the first position */
  if(new_node->data < head->data){
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
    return;
  }

  /* Temp iteration variables */
  dl_node_t *aux = head;

  /* Move iteration pointers */
  while(new_node->data >= aux->data && aux->next != NULL){
    aux = aux->next;
  }

  /* Insert on the end */
  if(new_node->data >= aux->data){
    new_node->prev = aux;
    aux->next = new_node;
    return;
  }
  
  /* Inset in the middle */
  aux->prev->next = new_node;
  new_node->next = aux;
  new_node->prev = aux->prev;
  aux->prev = new_node;

  return;
}

bool doubly_linked_remove(int32_t data){ 
  if(head == NULL) return false;
  
  /* Temp iteration variables */
  dl_node_t *aux = head;

  /* Delete first element */
  if(head->data == data){
    /* If the list has only one element, it is not necessary move next previous */
    if(aux->next != NULL) aux->next->prev = NULL;

    /* Set new head */
    head = aux->next; 

    /* Free up memory space for deleted Node */
    free(aux);
    length--;
    return true;
  }

  /* Move iteration pointers */
  while(aux->next != NULL){
    aux = aux->next;

    if(aux->data == data){
      /* Element on the end */
      if(aux->next == NULL) aux->prev->next = NULL;

      /* Element in the middle */
      if(aux->next != NULL) {
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
      }

      /* Free up memory space for deleted Node */
      free(aux);
      length--;
      return true;
    }
  }

  return false;
}

void doubly_linked_iteration(void (*iteration_fnc)(int32_t)){
  if(head == NULL) return;

  dl_node_t *aux = head;

  /* Execute generic received function for each element of doubly linked list */
  while(aux != NULL){
    iteration_fnc(aux->data);
    aux = aux->next;
  }

  return;
}

int32_t doubly_linked_length(){
  return length;
}

void doubly_linked_reverse(){
  dl_node_t *aux = head, *temp = NULL;

  while(aux != NULL){    
    /* Swap next/previous */
    temp = aux->next;
    aux->next = aux->prev;
    aux->prev = temp;

    /* Set new head when reach last element */
    if(aux->prev == NULL) head = aux;

    /* Move pointers */
    aux = aux->prev;
  }

  return;
}
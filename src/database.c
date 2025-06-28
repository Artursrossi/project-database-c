/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "../includes/array_list/array_list.h"
#include "../includes/doubly_linked_list/doubly_linked.h"
#include "../includes/binary_tree/binary_tree.h"

void doubly_linked_print_fnc(int32_t data) {
  printf("User: %d \n", data);
}

void handle_create_record(){
  user_t user;

  /* Get user input */
  printf("Digit your document (FORMAT: 000.000.000-00): \n");
  //clear_buffer();
  //fgets(user.document, DOCUMENT_LENGTH, stdin);
  //user.document[strcspn(user.document, "\n")] = '\0'; /* Remove newline (Enter) from stdin */

  scanf("%d", &user.temp_id);

  /* Verify if document is already in use */
  bool document_in_use = binary_tree_search(user.temp_id);
  if(document_in_use){
    printf("Document already in use\n");
    return;
  }

  /* Create the record */
  binary_tree_insert(user.temp_id);
  array_push(user.temp_id);
  doubly_linked_insert(user.temp_id);

  return;
}

void handle_update_record(){
  return;
}

void handle_delete_record(){
  int32_t temp_id = 0;

  /* Get user input */
  printf("Digit your document (FORMAT: 000.000.000-00): \n");
  //clear_buffer();
  //fgets(user.document, DOCUMENT_LENGTH, stdin);
  //user.document[strcspn(user.document, "\n")] = '\0'; /* Remove newline (Enter) from stdin */

  scanf("%d", &temp_id);

  /* Verify if document is already in use */
  bool is_document_found = binary_tree_search(temp_id);
  if(!is_document_found){
    printf("Document not found\n");
    return;
  }

  /* Delete document record */
  binary_tree_remove(temp_id);
  doubly_linked_remove(temp_id);

  return;
}

void handle_find_unique_record(){
  int32_t temp_id = 0;

  /* Get user input */
  printf("Digit your document (FORMAT: 000.000.000-00): \n");
  //clear_buffer();
  //fgets(user.document, DOCUMENT_LENGTH, stdin);
  //user.document[strcspn(user.document, "\n")] = '\0'; /* Remove newline (Enter) from stdin */
  
  scanf("%d", &temp_id);

  /* Verify if document is already in use */
  bool is_document_found = binary_tree_search(temp_id);
  if(!is_document_found){
    printf("Document not found\n");
    return;
  }

  printf("Index: %d", array_find(temp_id));

  return;
}

void handle_find_many_records(){
  doubly_linked_iteration(doubly_linked_print_fnc);
  
  return;
}
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

void clear_buffer(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void pretty_print_user(user_t user){
  printf("\n########## USER ##########\n");
  printf("User Document: %s \n", user.document);
  printf("User Name : %s \n", user.name);
  printf("User Email: %s \n", user.email);
  printf("User Phone: %s \n", user.phone);
  printf("User Address: %s \n", user.address);
  printf("##########################");

  return;
}

void doubly_linked_print_fnc(dl_node_data_t data) {
  user_t user = {0};

  ARRAY_RES array_get_res = array_get(data.index, &user);

  if(array_get_res != ARRAY_RES_OK) {
    printf("Error on doubly_linked_print_fnc function\n");
    return;
  }

  pretty_print_user(user);
  return;
}

void handle_create_record(){
  user_t user = {0};
  bt_node_data_t bt_node_data = {0};
  dl_node_data_t dl_node_data = {0};
  int32_t user_array_list_index = -1;

  /* Get user input */
  printf("Digit your document (FORMAT: 000.000.000-00): \n");
  clear_buffer();
  fgets(user.document, DOCUMENT_LENGTH, stdin);
  user.document[strcspn(user.document, "\n")] = '\0'; /* Remove newline (Enter) from stdin */

  /* Verify if document is already in use */
  bool document_in_use = binary_tree_search(user.document, NULL);
  if(document_in_use){
    printf("Document already in use\n");
    return;
  }

  /* Create the main record */
  ARRAY_RES array_push_res = array_push(user, &user_array_list_index);
  if(array_push_res != ARRAY_RES_OK){
    printf("Error on array_push_res function\n");
    return;
  }
  if(user_array_list_index == -1){
    printf("Invalid user index on array_list\n");
    return;
  }
  
  /* Copy user data to auxiliar variables */
  strcpy(bt_node_data.document, user.document);
  strcpy(dl_node_data.name, user.name);

  /* Copy array_list index to auxiliar variables */
  bt_node_data.index = user_array_list_index;
  dl_node_data.index = user_array_list_index;

  binary_tree_insert(bt_node_data);
  doubly_linked_insert(dl_node_data);

  return;
}

void handle_update_record(){
  return;
}

void handle_delete_record(){
  user_t user = {0};

  /* Get user input */
  printf("Digit your document (FORMAT: 000.000.000-00): \n");
  clear_buffer();
  fgets(user.document, DOCUMENT_LENGTH, stdin);
  user.document[strcspn(user.document, "\n")] = '\0'; /* Remove newline (Enter) from stdin */

  /* Verify if document is already in use */
  bool is_document_found = binary_tree_search(user.document, NULL);
  if(!is_document_found){
    printf("Document not found\n");
    return;
  }

  /* Delete document record */
  binary_tree_remove(user.document);
  doubly_linked_remove(user.name);

  return;
}

void handle_find_unique_record(){
  user_t user = {0};
  bt_node_data_t temp_searched_data = {0};

  /* Get user input */
  printf("Digit your document (FORMAT: 000.000.000-00): \n");
  clear_buffer();
  fgets(user.document, DOCUMENT_LENGTH, stdin);
  user.document[strcspn(user.document, "\n")] = '\0'; /* Remove newline (Enter) from stdin */
  
  /* Verify if document is already in use */
  bool is_document_found = binary_tree_search(user.document, &temp_searched_data);
  if(!is_document_found){
    printf("Document not found\n");
    return;
  }

  ARRAY_RES array_get_res = array_get(temp_searched_data.index, &user);

  if(array_get_res != ARRAY_RES_OK) {
    printf("Error on doubly_linked_print_fnc function\n");
    return;
  }

  pretty_print_user(user);

  return;
}

void handle_find_many_records(){
  doubly_linked_iteration(doubly_linked_print_fnc);
  
  return;
}
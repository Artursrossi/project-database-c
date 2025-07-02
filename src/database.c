/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "data_structures/array_list/array_list.h"
#include "data_structures/doubly_linked_list/doubly_linked.h"
#include "data_structures/binary_tree/binary_tree.h"
#include "utils.h"

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

  /* Flush stdin */
  clear_buffer();

  /* Get user document */
  prompt_user_document(user.document);

  /* Verify if document is already in use */
  bool document_in_use = binary_tree_search(user.document, NULL);
  if(document_in_use){
    printf("Document already in use\n");
    return;
  }

  /* Get user name */
  prompt_user_name(user.name, false);

  /* Get user email */
  prompt_user_email(user.email, false);

  /* Get user phone */
  printf("Digit your phone: \n");
  fgets(user.phone, PHONE_LENGTH, stdin);
  user.phone[strcspn(user.phone, "\n")] = '\0'; /* Remove newline (Enter) from stdin */

  /* Get user address */
  printf("Digit your address: \n");
  fgets(user.address, ADDRESS_LENGTH, stdin);
  user.address[strcspn(user.address, "\n")] = '\0'; /* Remove newline (Enter) from stdin */

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
  user_t new_user = {0};
  user_t current_user = {0};
  bt_node_data_t bt_node_data = {0};
  dl_node_data_t dl_node_data = {0};

  /* Flush stdin */
  clear_buffer();

  /* Get user document */
  prompt_user_document(new_user.document);

  /* Verify if document is already in use */
  bool is_document_found = binary_tree_search(new_user.document, &bt_node_data);
  if(!is_document_found){
    printf("Document not found\n");
    return;
  }

  /* Get user name */
  prompt_user_name(new_user.name, true);
  
  /* Get user email */
  prompt_user_email(new_user.email, true);
  
  /* Get user phone */
  printf("Digit your phone: \n");
  fgets(new_user.phone, PHONE_LENGTH, stdin);
  new_user.phone[strcspn(new_user.phone, "\n")] = '\0'; /* Remove newline (Enter) from stdin */
  
  /* Get user address */
  printf("Digit your address: \n");
  fgets(new_user.address, ADDRESS_LENGTH, stdin);
  new_user.address[strcspn(new_user.address, "\n")] = '\0'; /* Remove newline (Enter) from stdin */
  
  /* Recover current user information */
  array_get(bt_node_data.index, &current_user);

  /* Skip empty strings */
  if(strcmp(new_user.name, "\0") == 0) strcpy(new_user.name, current_user.name);
  if(strcmp(new_user.email, "\0") == 0) strcpy(new_user.email, current_user.email);
  if(strcmp(new_user.phone, "\0") == 0) strcpy(new_user.phone, current_user.phone);
  if(strcmp(new_user.address, "\0") == 0) strcpy(new_user.address, current_user.address);

  /* Create the main record */
  ARRAY_RES array_push_res = array_set(bt_node_data.index, new_user);
  if(array_push_res != ARRAY_RES_OK){
    printf("Error on array_push_res function\n");
    return;
  }

  /* Insert new name, if necessary */
  if(strcmp(new_user.name, "\0") != 0){
    doubly_linked_remove(current_user.name);

    dl_node_data.index = bt_node_data.index;
    strcpy(dl_node_data.name, new_user.name);

    doubly_linked_insert(dl_node_data);
  }

  return;
}

void handle_delete_record(){
  user_t user = {0};
  bt_node_data_t bt_node_data = {0};

  /* Flush stdin */
  clear_buffer();

  /* Get user document */
  prompt_user_document(user.document);

  /* Verify if document is already in use */
  bool is_document_found = binary_tree_search(user.document, &bt_node_data);
  if(!is_document_found){
    printf("Document not found\n");
    return;
  }

  /* Recover current user information */
  array_get(bt_node_data.index, &user);

  /* Delete document record */
  binary_tree_remove(user.document);
  doubly_linked_remove(user.name);

  return;
}

void handle_find_unique_record(){
  user_t user = {0};
  bt_node_data_t temp_searched_data = {0};

  /* Flush stdin */
  clear_buffer();

  /* Get user document */
  prompt_user_document(user.document);
  
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
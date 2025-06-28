/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include "menu.h"
#include "../includes/array_list/array_list.h"
#include "../includes/doubly_linked_list/doubly_linked.h"
#include "../includes/binary_tree/binary_tree.h"

int main(void){
  array_init();

  menu_init();

  array_destroy();
  doubly_linked_destroy();
  binary_tree_destroy();

  return 0;
}
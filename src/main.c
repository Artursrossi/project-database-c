/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include "menu.h"
#include "data_structures/array_list/array_list.h"
#include "data_structures/doubly_linked_list/doubly_linked.h"
#include "data_structures/binary_tree/binary_tree.h"

int main(void){
  array_init();

  menu_init();

  array_destroy();
  doubly_linked_destroy();
  binary_tree_destroy();

  return 0;
}
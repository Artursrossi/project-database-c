/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "menu.h"

static void display_main_menu(uint16_t *opt){
  printf("\n\nChoose a database table iteration \n");
  printf("%d - Create a record \n", OPT_CREATE);
  printf("%d - Update a record \n", OPT_UPDATE);
  printf("%d - Delete a record \n", OPT_DELETE);
  printf("%d - Find unique record \n", OPT_FIND_UNIQUE);
  printf("%d - Generate a report \n", OPT_FIND_MANY);
  printf("%d - Quit \n", OPT_QUIT);

  scanf("%hu", opt);
}

static void handle_main_menu(){
  uint16_t opt = 0;

  do{
    display_main_menu(&opt);
    
    switch(opt){
      case OPT_CREATE:

        break;
      
      case OPT_UPDATE:
        break;

      case OPT_DELETE:
        break;

      case OPT_FIND_UNIQUE:
        break;

      case OPT_FIND_MANY:
        break;
    }
  }while(opt != OPT_QUIT);
}

void menu_init(){
  handle_main_menu();
}
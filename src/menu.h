/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef MENU_H
#define MENU_H

/* Constants */
enum{
  OPT_CREATE = 1,
  OPT_UPDATE,
  OPT_DELETE,
  OPT_FIND_UNIQUE,
  OPT_FIND_MANY,
  OPT_QUIT
};

/* Functions prototypes */

/**
 * @brief Initialize menus flow
*/
void menu_init();

#endif // MENU_H
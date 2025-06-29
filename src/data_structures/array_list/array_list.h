/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stdint.h>

#include "../../database.h"

/* Constants */
enum {
  ARRAY_INITIAL_SIZE = 8,
  ARRAY_GROWTH_QNT = 4
};
typedef enum {
  ARRAY_RES_OK,
  ARRAY_RES_EMPTY,
  ARRAY_RES_NOT_FOUND,
  ARRAY_RES_NOT_INITIALIZED
} ARRAY_RES;

/* Functions prototypes */

/**
 * @brief Initialize dynamic variables, allocating an initial size for array list
*/
void array_init();

/**
 * @brief Free up the space allocated by the function array_init
*/
void array_destroy();

/**
 * @brief Get value by index
 * 
 * @param index Index of element to be getted
 * @param getted_value Pointer of variable that will receive getted value
*/
ARRAY_RES array_get(int32_t index, user_t *getted_value);

/**
 * @brief Push an element to the top of array list
 * 
 * @param value Value to be added
*/
ARRAY_RES array_push(user_t value, int32_t *value_index);

/**
 * @brief Replace (update) an array list element by index
 * 
 * @param index Index of element to be replaced
 * @param new_value New element to replace the old one
*/
ARRAY_RES array_set(int32_t index, user_t new_value);

#endif //ARRAY_LIST_H

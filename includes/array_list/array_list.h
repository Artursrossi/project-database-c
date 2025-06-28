/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdbool.h>
#include <stdint.h>

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
 * @brief Clone array list elements to an external variable
 * 
 * @param p_array_dump Pointer of variable that will receive array list elements
*/
ARRAY_RES array_dump(int32_t **p_array_dump);

/**
 * @brief Returns the number of elements in array list, avoiding overlapping the value of array_position
 * 
 * @return Number of elements in array list
*/
int32_t array_length();

/**
 * @brief Find index of value inside array list
 * 
 * @param value Value to be searched
 * 
 * @return Index of value (returns -1 for not found)
*/
int32_t array_find(int32_t value);

/**
 * @brief Get value by index
 * 
 * @param index Index of element to be getted
 * @param getted_value Pointer of variable that will receive getted value
*/
ARRAY_RES array_get(int32_t index, int32_t *getted_value);

/**
 * @brief Push an element to the top of array list
 * 
 * @param value Value to be added
*/
ARRAY_RES array_push(int32_t value);

/**
 * @brief Remove the element on the top of array list
 * 
 * @param removed_value Pointer of variable that will receive popped value
*/
ARRAY_RES array_pop(int32_t *removed_value);

/**
 * @brief Remove element by value
 * 
 * @param value Element to be removed
*/
ARRAY_RES array_remove(int32_t value);

/**
 * @brief Replace (update) an array list element by index
 * 
 * @param index Index of element to be replaced
 * @param new_value New element to replace the old one
*/
ARRAY_RES array_set(int32_t index, int32_t new_value);

/**
 * @brief Sort array list elements ordering by asc or desc
 * 
 * @param is_asc True for ordering by ascending and False for descending
*/
ARRAY_RES array_sort(bool is_asc);

#endif //ARRAY_LIST_H

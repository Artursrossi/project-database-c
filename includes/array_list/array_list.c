/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>

#include "array_list.h"

/* Variables */
static user_t *array = NULL;
static int32_t array_position = 0;
static int32_t array_max_size = 0;

void array_init(){
    if(array != NULL) return;

    /* Allocate memory space (in BYTES) for array list, using ARRAY_INITIAL_SIZE */
    array = (user_t *) malloc(ARRAY_INITIAL_SIZE * sizeof(user_t));
    if(array == NULL){
        perror("A memory allocation error has occurred. (array_list.c) \n");
        exit(EXIT_FAILURE);
    }

    array_max_size = ARRAY_INITIAL_SIZE;
}

void array_destroy(){
    if(array == NULL) return;
  
    /* Free up memory space for array list */
    free(array);
    array = NULL;
}

static bool array_full() {  
    return array_position == array_max_size;
}

static bool array_empty() {  
    return array_position == 0;
}

static void array_grow() {
    int32_t temp_max_size = array_max_size + ARRAY_GROWTH_QNT;
    
    /* Increase memory space of array list, allocating more BYTES */
    array = (user_t *) realloc(array, temp_max_size * sizeof(user_t));
    if(array == NULL){
        perror("A memory allocation error has occurred. (array_list.c) \n");
        exit(EXIT_FAILURE);
    }
    
    array_max_size = temp_max_size;
}

ARRAY_RES array_get(int32_t index, user_t *getted_value){
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;
    if(array_empty()) return ARRAY_RES_EMPTY;

    /* Verify if the index is valid (do not accept negative or higher than actual list) */
    if(index >= array_position || index < 0) return ARRAY_RES_NOT_FOUND;

    *getted_value = array[index];

    return ARRAY_RES_OK;
}

ARRAY_RES array_push(user_t value, int32_t *value_index) {
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;

    /* If array container is full, reallocate more memory */
    if (array_full()) array_grow();
    
    array[array_position] = value;
    *value_index = array_position;
    array_position++;

    return ARRAY_RES_OK;
}

ARRAY_RES array_set(int32_t index, user_t new_value){
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;
    if(array_empty()) return ARRAY_RES_EMPTY;

    /* Verify if the index is valid (do not accept negative or higher than actual list) */
    if(index >= array_position || index < 0) return ARRAY_RES_NOT_FOUND;

    array[index] = new_value;

    return ARRAY_RES_OK;
}
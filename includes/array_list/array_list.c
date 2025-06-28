/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>

#include "array_list.h"

/* Variables */
static int32_t *array = NULL;
static int32_t array_position = 0;
static int32_t array_max_size = 0;

void array_init(){
    if(array != NULL) return;

    /* Allocate memory space (in BYTES) for array list, using ARRAY_INITIAL_SIZE */
    array = (int32_t *) malloc(ARRAY_INITIAL_SIZE * sizeof(int32_t));
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

ARRAY_RES array_dump(int32_t **p_array_dump){
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;
    if (array_empty()) return ARRAY_RES_EMPTY;
  
    /* Allocate memory space (in BYTES) for external array list variable */
    *p_array_dump = (int32_t*) malloc(array_position * sizeof(int32_t));
    if((*p_array_dump) == NULL){
      perror("A memory allocation error has occurred. (array_list.c) \n");
      exit(EXIT_FAILURE);
    }
  
    /* Clone each elements of list to an external array list variable */
    for(int32_t i = 0; i < array_position; i++){
      (*p_array_dump)[i] = array[i];
    }
  
    return ARRAY_RES_OK;
  }

static void array_grow() {
    int32_t temp_max_size = array_max_size + ARRAY_GROWTH_QNT;
    
    /* Increase memory space of array list, allocating more BYTES */
    array = (int32_t *) realloc(array, temp_max_size * sizeof(int32_t));
    if(array == NULL){
        perror("A memory allocation error has occurred. (array_list.c) \n");
        exit(EXIT_FAILURE);
    }
    
    array_max_size = temp_max_size;
}

int32_t array_length() {
    return array_position;
}

int32_t array_find(int32_t value){
    if(array == NULL || array_empty()) return -1;

    /* Search for value */
    for(int32_t i = 0; i < array_position; i++){
        if(array[i] == value) return i;
    }

    return -1;
}

ARRAY_RES array_get(int32_t index, int32_t *getted_value){
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;
    if(array_empty()) return ARRAY_RES_EMPTY;

    /* Verify if the index is valid (do not accept negative or higher than actual list) */
    if(index >= array_position || index < 0) return ARRAY_RES_NOT_FOUND;

    *getted_value = array[index];

    return ARRAY_RES_OK;
}

ARRAY_RES array_push(int32_t value) {
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;

    /* If array container is full, reallocate more memory */
    if (array_full()) array_grow();
    
    array[array_position] = value;
    array_position++;

    return ARRAY_RES_OK;
}

ARRAY_RES array_pop(int32_t *removed_value) {
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;
    if(array_empty()) return ARRAY_RES_EMPTY;

    *removed_value = array[array_position - 1];
    array_position--;

    return ARRAY_RES_OK;
}

ARRAY_RES array_remove(int32_t value) {
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;
    if(array_empty()) return ARRAY_RES_EMPTY;

    /* Verify if value exists, and get index */
    int32_t index = array_find(value);
    if(index == -1) return ARRAY_RES_NOT_FOUND;

    /* Move all objects to one lower, overlapping removed element */
    while(index < array_position){
        array[index] = array[index+1];
        index++;
    }

    array_position--;

    return ARRAY_RES_OK;
}

ARRAY_RES array_set(int32_t index, int32_t new_value){
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;
    if(array_empty()) return ARRAY_RES_EMPTY;

    /* Verify if the index is valid (do not accept negative or higher than actual list) */
    if(index >= array_position || index < 0) return ARRAY_RES_NOT_FOUND;

    array[index] = new_value;

    return ARRAY_RES_OK;
}

/* Native qsort function order by asc */
static int sort_compar_asc(const void *a, const void *b){
    return (*(int32_t*)a - *(int32_t*)b);
}

/* Native qsort function order by desc */
static int sort_compar_desc(const void *a, const void *b){
    return (*(int32_t*)b - *(int32_t*)a);
}

ARRAY_RES array_sort(bool is_asc) {
    if(array == NULL) return ARRAY_RES_NOT_INITIALIZED;
    if(array_empty()) return ARRAY_RES_EMPTY;
    if(array_position == 1) return ARRAY_RES_OK;

    /* Switch between ASC and DESC functions */
    __compar_fn_t compar_fn = is_asc ? sort_compar_asc : sort_compar_desc;

    qsort(array, array_position, sizeof(int32_t), compar_fn);

    return ARRAY_RES_OK;
}
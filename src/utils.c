/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "database.h"

void clear_buffer(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

bool is_valid_document_format(const char *document) {
  if (strlen(document) != 14) return false;

  /* Check format: 000.000.000-00 */ 
  for (int i = 0; i < 14; i++) {
    /* Check dots location */
    if(i == 3 || i == 7){
      if (document[i] != '.') return false;
      continue;
    }

    /* Check hyphen */
    if (i == 11) {
      if (document[i] != '-') return false;
      continue;  
    } 

    if(!isdigit((unsigned char)document[i])) return false;
  }

  return true;
}

void prompt_document(char *document) {
  do {
      printf("Digit your document (FORMAT: 000.000.000-00): \n");

      /* Get user document */
      if (fgets(document, DOCUMENT_LENGTH, stdin) == NULL) {
        perror("Invalid stdin input on prompt_document function. (utils.h) \n");
        exit(EXIT_FAILURE);
      }

      /* Remove newline (Enter) from stdin */
      document[strcspn(document, "\n")] = '\0';

  } while (!is_valid_document_format(document));
}
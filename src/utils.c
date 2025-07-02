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

void prompt_user_document(char *document) {
  do {
    printf("Digit your document (FORMAT: 000.000.000-00): \n");

    /* Get user document */
    if (fgets(document, DOCUMENT_LENGTH, stdin) == NULL) {
      perror("Invalid stdin input on prompt_user_document function. (utils.c) \n");
      exit(EXIT_FAILURE);
    }

    /* Remove newline (Enter) from stdin */
    document[strcspn(document, "\n")] = '\0';

  } while (!is_valid_document_format(document));
}

void prompt_user_name(char *name, bool skip_validation) {
  do {
    printf("Digit your full name: \n");

    /* Get user name */
    if (fgets(name, USERNAME_LENGTH, stdin) == NULL) {
      perror("Invalid stdin input on prompt_user_name function. (utils.c) \n");
      exit(EXIT_FAILURE);
    }

    /* Remove newline (Enter) from stdin */
    name[strcspn(name, "\n")] = '\0';

    /* Skip validations for Update Record function */
    if(skip_validation && strcmp(name, "\0") == 0) break;

    if(strlen(name) < 4) {
      printf("Your name must contain at least 4 characters. \n");
      continue;
    }

    if (strlen(name) > 64) {
      printf("Your name must have a maximum of 64 characters. \n");
      continue;
    }

    break;
  } while (1);
}

bool is_valid_email_format(char *email) {
  /* Email need to at least 4 characters */
  if(strlen(email) < 4) {
    printf("Your email must contain at least 4 characters. \n");
    return false;
  }

  /* Email must have a maximum of 48 characters */
  if (strlen(email) > 48) {
    printf("Your email must have a maximum of 48 characters. \n");
    return false;
  }

  /* Validate if email has @ */
  for (int i = 0; email[i] != '\0'; i++) {
    if (email[i] == '@') return true;
  }

  printf("Invalid email format. \n");
  return false;
}

void prompt_user_email(char *email, bool skip_validation) {
  do {
    printf("Digit your email: \n");

    /* Get user email */
    if (fgets(email, EMAIL_LENGTH, stdin) == NULL) {
      perror("Invalid stdin input on prompt_user_email function. (utils.c) \n");
      exit(EXIT_FAILURE);
    }

    /* Remove newline (Enter) from stdin */
    email[strcspn(email, "\n")] = '\0';

    /* Skip validations for Update Record function */
    if(skip_validation && strcmp(email, "\0") == 0) break;

  } while (!is_valid_email_format(email));
}

void prompt_user_address(char *address, bool skip_validation) {
  do {
    printf("Digit your address: \n");

    /* Get user address */
    if (fgets(address, ADDRESS_LENGTH, stdin) == NULL) {
      perror("Invalid stdin input on prompt_user_address function. (utils.c) \n");
      exit(EXIT_FAILURE);
    }

    /* Remove newline (Enter) from stdin */
    address[strcspn(address, "\n")] = '\0';

    /* Skip validations for Update Record function */
    if(skip_validation && strcmp(address, "\0") == 0) break;

    if(strlen(address) < 4) {
      printf("Your address must contain at least 4 characters. \n");
      continue;
    }

    if (strlen(address) > 128) {
      printf("Your address must have a maximum of 128 characters. \n");
      continue;
    }

    break;
  } while (1);
}
/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <stdint.h>
#include <stdbool.h>

/* Constants */
enum{
  DOCUMENT_LENGTH = 16, // CPF: "000.000.000-00" + '\n' + '\0'
  USERNAME_LENGTH = 64,
  EMAIL_LENGTH = 48,
  PHONE_LENGTH = 17, // PHONE: "(00) 00000-0000" + '\n' + '\0'
  ADDRESS_LENGTH  = 128
};

struct User {
  char document[DOCUMENT_LENGTH];
  char name[USERNAME_LENGTH];
  char email[EMAIL_LENGTH];
  char phone[PHONE_LENGTH];
  char address[ADDRESS_LENGTH];
};
typedef struct User user_t;

/* Functions prototypes */

void handle_create_record();
void handle_update_record();
void handle_delete_record();
void handle_find_unique_record();
void handle_find_many_records();

#endif // DATABASE_H
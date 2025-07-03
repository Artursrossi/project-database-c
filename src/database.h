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
  USERNAME_LENGTH = 66, // 64 Characters + '\n' + '\0'
  EMAIL_LENGTH = 50, // 48 Characters + '\n' + '\0'
  PHONE_LENGTH = 17, // PHONE: "(00) 00000-0000" + '\n' + '\0'
  ADDRESS_LENGTH  = 130 // 128 Characters + '\n' + '\0'
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

/**
 * @brief Create a new user record
 */
void handle_create_record();

/**
 * @brief Update an existing user record
 */
void handle_update_record();

/**
 * @brief Delete a user record by document
 */
void handle_delete_record();

/**
 * @brief Find and display a user by document
 */
void handle_find_unique_record();

/**
 * @brief Display all users
 */
void handle_find_many_records();

#endif // DATABASE_H
/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef UTILS_H
#define UTILS_H

/* Functions prototypes */

void clear_buffer();

bool is_valid_document_format(const char *document);
void prompt_user_document(char *document);

void prompt_user_name(char *name, bool skip_validation);

bool is_valid_email_format(char *email);
void prompt_user_email(char *email, bool skip_validation);

bool is_valid_phone_format(const char *phone);
void prompt_user_phone(char *phone, bool skip_validation);

void prompt_user_address(char *address, bool skip_validation);

#endif // UTILS_H
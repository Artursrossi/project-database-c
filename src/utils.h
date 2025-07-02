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

#endif // UTILS_H
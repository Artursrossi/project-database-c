/**
* Author: Artur Schincariol Rossi <schincariolartur@gmail.com>
*/

#ifndef UTILS_H
#define UTILS_H

/* Functions prototypes */

/**
 * @brief Clears the stdin buffer
 */
void clear_buffer();

/**
 * @brief Validates if a document matches the CPF format "000.000.000-00"
 * 
 * @param document String containing the document to validate
 * 
 * @return true if the format is valid, false otherwise
 */
bool is_valid_document_format(const char *document);

/**
 * @brief Prompts the user to enter a valid document
 * 
 * @param document Pointer to char vector where the input will be stored
 */
void prompt_user_document(char *document);

/**
 * @brief Prompts the user to enter a valid full name
 * 
 * @param name Pointer to a char vector where the input will be stored
 * @param skip_validation Allows skipping length validation, accepting "\0" input (empty string)
 */
void prompt_user_name(char *name, bool skip_validation);

/**
 * @brief Validates if an email has a valid format
 * 
 * @param email String containing the email to validate
 * @return true if the format is valid, false otherwise
 */
bool is_valid_email_format(char *email);

/**
 * @brief Prompts the user to enter a valid email
 * 
 * @param email Pointer to a char vector where the input will be stored
 * @param skip_validation Allows skipping length validation, accepting "\0" input (empty string)
 */
void prompt_user_email(char *email, bool skip_validation);

/**
 * @brief Validates if a phone number matches the format "(00) 00000-0000"
 * 
 * @param phone String containing the phone number to validate
 * @return true if the format is valid, false otherwise
 */
bool is_valid_phone_format(const char *phone);

/**
 * @brief Prompts the user to enter a valid phone number
 * 
 * @param phone Pointer to a char vector where the input will be stored
 * @param skip_validation Allows skipping length validation, accepting "\0" input (empty string)
 */
void prompt_user_phone(char *phone, bool skip_validation);

/**
 * @brief Prompts the user to enter a valid address
 * 
 * @param address Pointer to a char vector where the input will be stored
 * @param skip_validation Allows skipping length validation, accepting "\0" input (empty string)
 */
void prompt_user_address(char *address, bool skip_validation);

#endif // UTILS_H
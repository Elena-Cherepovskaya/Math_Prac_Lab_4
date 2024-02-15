//
//  custom_string.h
//  4
//
//  Created by Лена on 02.02.2024.
//

#ifndef custom_string_h
#define custom_string_h

#include <stdbool.h>

typedef struct
{
    char* data;
    int len;
    int capacity;
}T_string;

enum status_codes create_string(T_string** string);
enum status_codes add_to_string(T_string* string, char c);
enum status_codes clear_string (T_string* string);
enum status_codes free_string (T_string** string);
bool string_comp(T_string *, char const *  str);

#endif /* custom_string_h */

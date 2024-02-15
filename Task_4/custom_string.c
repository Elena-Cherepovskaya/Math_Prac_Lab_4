//
//  custom_string.c
//  4
//
//  Created by Лена on 02.02.2024.
//

#define START_CAPACITY 32

#include "custom_string.h"
#include "status_codes.h"

#include <stdlib.h>
#include <string.h>

enum status_codes create_string(T_string** string)
{
    if (*string == NULL)
    {
        *string = (T_string*)malloc(sizeof(T_string));
        if (*string != NULL)
        {
            (*string)->data = (char*)malloc(sizeof(char) * START_CAPACITY);
            if ((*string)->data == NULL)
            {
                free(*string);
                *string = NULL;
                return fsc_memory_error_detected;
            }
            (*string)->len = 0;
            (*string)->capacity = START_CAPACITY;
        }
        return fsc_ok;
    }
    return fsc_invalid_parameter;
}

enum status_codes add_to_string(T_string* string, char c)
{    
    // todo Добавить realloc
    string->data[string->len] = c;
    string->data[string->len + 1] = 0;
    ++(string->len);
    
    return fsc_ok;
}

enum status_codes clear_string(T_string* string)
{
    string->data[0] = 0;
    string->len = 0;
    return fsc_ok;
}

enum status_codes free_string(T_string** string)
{
    if (*string == NULL)
        return fsc_invalid_parameter;
    
    free((*string)->data);
    free(*string);
    *string = NULL;
    
    return fsc_ok;
}

bool string_comp(T_string *string, char const *  str)
{
    return strcmp(string->data, str) == 0;
}


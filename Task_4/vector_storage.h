//
//  vector_storage.h
//  4
//
//  Created by Лена on 02.02.2024.
//

#ifndef vector_storage_h
#define vector_storage_h

#include <stdio.h>

#include "vector_name.h"
#include "status_codes.h"

typedef struct
{
    T_vector_name** data;
    int len;
    int capacity;
}T_vector_storage;

enum status_codes create_vector_storage(T_vector_storage** storage);
enum status_codes get_vector(T_vector_storage* storage, char name, T_vector_name** vector_name);
enum status_codes print_vector_storage(T_vector_storage* storage, FILE* output);
enum status_codes clear_vector_storage(T_vector_storage** storage);

//enum status_codes create_vector_storage(T_vector_storage** storage);
//enum status_codes add_to_vector_starage(T_vector_storage** storage, T_vector_name* vector_name);
//enum status_codes find_vector_in_storage(T_vector** res, T_vector_storage* storage, char vector_name);
//enum status_codes change_vactor_in_storage(T_vector_storage* storage, char name, int value);
//enum status_codes is_vector_in_storage(T_vector_storage* storage, char name);

#endif /* vector_storage_h */

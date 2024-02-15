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

enum status_codes vector_storage_get_vector(T_vector_storage* storage, char name, T_vector_name** vector_name);
enum status_codes vector_storage_set_vector(T_vector_storage* storage, char name, int value);

enum status_codes print_vector_storage(T_vector_storage* storage, FILE* output);
enum status_codes clear_vector_storage(T_vector_storage** storage);
enum status_codes free_vector_storage (T_vector_storage** storage);

#endif /* vector_storage_h */

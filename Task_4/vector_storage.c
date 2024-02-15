//
//  vector_storage.c
//  4
//
//  Created by Лена on 02.02.2024.
//

#define START_CAPACITY 32

#include "vector_storage.h"

#include "bool_vector.h"
#include "vector_name.h"

#include <stdlib.h>

enum status_codes clear_vector_storage(T_vector_storage** storage)
{
    if (*storage != NULL)
    {
        free((*storage)->data);
        free(*storage);
        *storage = NULL;

        return fsc_ok;
    }
    return fsc_invalid_parameter;
}

enum status_codes create_vector_storage(T_vector_storage** storage)
{
    if (*storage != NULL)
        return fsc_invalid_parameter;
    
    *storage = (T_vector_storage*)malloc(sizeof(T_vector_storage));
    if (*storage == NULL)
        return fsc_memory_error_detected;
    
    (*storage)->data = (T_vector_name**)malloc(sizeof(T_vector_name) * START_CAPACITY);
    if ((*storage)->data == NULL)
    {
        free(*storage);
        *storage = NULL;
        return fsc_memory_error_detected;
    }
    
    (*storage)->len = 0;
    (*storage)->capacity = START_CAPACITY;
    
    return fsc_ok;
}

enum status_codes add_to_vector_starage(T_vector_storage** storage, T_vector_name* vector_name)
{
    enum status_codes res = fsc_ok;
    
    if (*storage == NULL)
        res = create_vector_storage(storage);
    
    if (res != fsc_ok)
        return res;
    
    if ((*storage)->len == (*storage)->capacity)
    {
        T_vector_name** tmp_p = realloc((*storage)->data, (*storage)->capacity * 2);
        if (*tmp_p == NULL)
        {
            clear_vector_storage(storage);
            return fsc_memory_error_detected;
        }
        
        (*storage)->data = tmp_p;
        (*storage)->capacity *= 2;
    }
    
    ((*storage)->data)[(*storage)->len] = vector_name;
    ++((*storage)->len);
    
    return fsc_ok;
}

enum status_codes find_vector_in_storage(T_vector** res, T_vector_storage* storage, char vector_name)
{
    if (*res != NULL)
        return fsc_invalid_parameter;
    
    *res = (T_vector*)malloc(sizeof(T_vector));
    if (*res == NULL)
        return fsc_memory_error_detected;
    
    if (storage != NULL)
    {
        for (int i = 0; i < storage->len; ++i)
        {
            if ((storage->data)[i]->name == vector_name)
            {
                *res = (storage->data)[i]->data;
                return fsc_ok;
            }
        }
        
        return fsc_vector_is_not_found;
    }
    
    return fsc_invalid_parameter;
}

enum status_codes change_vactor_in_storage(T_vector_storage* storage, char name, int value)
{
    if (storage == NULL)
        return fsc_invalid_parameter;
    
    for (int i = 0; i < storage->len; ++i)
    {
        if ((storage->data)[i]->name == name)
        {
            (storage->data)[i]->data->data = value;
            return fsc_ok;
        }
    }
    
    return fsc_vector_is_not_found;
}

enum status_codes is_vector_in_storage(T_vector_storage* storage, char name)
{
    if (storage == NULL)
        return fsc_invalid_parameter;
    
    for (int i = 0; i < storage->len; ++i)
    {
        if ((storage->data)[i]->name == name)
            return fsc_is_detected;
    }
    return fsc_is_not_detected;
}

enum status_codes print_vector_storage(T_vector_storage* storage, FILE* output)
{
    if (output == NULL || storage == NULL)
        return fsc_is_detected;
    
    for (int i = 0; i < storage->len; ++i)
        fprintf(output, "%c %d\n", (storage->data)[i]->name, (storage->data)[i]->data->data);
    
    return fsc_ok;
}

enum status_codes get_vector(T_vector_storage* storage, char name, T_vector_name** vector_name)
{
    if ((storage == NULL) || (*vector_name != NULL))
        return fsc_invalid_parameter;
    
    for (int i = 0; i < storage->len; ++i)
    {
        if ((storage->data)[i]->name == name)
        {
            *vector_name = (T_vector_name*)malloc(sizeof(T_vector_name));
            if (*vector_name == NULL)
                return fsc_invalid_parameter;
            
            (*vector_name)->name = name;
            (*vector_name)->data = (storage->data)[i]->data;
            
            return fsc_is_detected;
        }
    }
    
    return fsc_is_not_detected;
}

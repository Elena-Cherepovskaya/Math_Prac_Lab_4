//
//  vector_name.c
//  4
//
//  Created by Лена on 01.02.2024.
//

#include "vector_name.h"
#include "bool_vector.h"

#include <stdlib.h>
#include "bool_vector.h"
#include "status_codes.h"

enum status_codes create_vector_name(T_vector_name** vector_name, char name, int value)
{
    if (*vector_name != NULL)
        return fsc_invalid_parameter;
    
    *vector_name = (T_vector_name*)malloc(sizeof(T_vector_name));
    if (*vector_name == NULL)
        return fsc_memory_error_detected;
    
    (*vector_name)->data = (T_vector*)malloc(sizeof(T_vector));
    if ((*vector_name)->data == NULL)
    {
        free(*vector_name);
        *vector_name = NULL;
        return fsc_memory_error_detected;
    }
    
    (*vector_name)->data->data = value;
    (*vector_name)->name = name;
    
    return fsc_ok;
}

enum status_codes clear_vector_name(T_vector_name** vector_name)
{
    if (*vector_name == NULL)
        return fsc_invalid_parameter;
    
    free(*vector_name);
    *vector_name = NULL;
    
    return fsc_ok;
}

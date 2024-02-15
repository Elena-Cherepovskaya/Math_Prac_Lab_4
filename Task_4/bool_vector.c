//
//  bool_vector.c
//  4
//
//  Created by Лена on 01.02.2024.
//

#include "bool_vector.h"
#include "status_codes.h"
#include "transform_x_to_10.h"

#include <stdlib.h>

enum status_codes num_to_vector(T_vector** vector, char* num, int base)
{
    if (*vector != NULL)
        return fsc_invalid_parameter;
    
    *vector = (T_vector*)malloc(sizeof(T_vector));
    if (*vector == NULL)
        return  fsc_memory_error_detected;
    
    return transform_x_to_10(&((*vector)->data), num, base);
}

enum status_codes clear_vector(T_vector** vector)
{
    if (*vector == NULL)
        return fsc_invalid_parameter;
    
    free(*vector);
    *vector = NULL;
    
    return fsc_ok;
}

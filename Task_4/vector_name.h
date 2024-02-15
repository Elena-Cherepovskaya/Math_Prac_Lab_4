//
//  vector_name.h
//  4
//
//  Created by Лена on 01.02.2024.
//

#ifndef vector_name_h
#define vector_name_h

#include <stdio.h>

#include "bool_vector.h"
#include "status_codes.h"

typedef struct
{
    T_vector* data;
    char name;
}T_vector_name;

enum status_codes create_vector_name(T_vector_name** vector_name, char name, int value);
enum status_codes clear_vector_name(T_vector_name** vector_name);

#endif /* vector_name_h */

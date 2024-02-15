//
//  bool_vector.h
//  4
//
//  Created by Лена on 01.02.2024.
//

#ifndef bool_vector_h
#define bool_vector_h

#include <stdio.h>

typedef struct
{
    int data;
}T_vector;

enum status_codes num_to_vector(T_vector** vector, char* num, int base);
enum status_codes clear_vector(T_vector** vector);

#endif /* bool_vector_h */

//
//  operations.h
//  4
//
//  Created by Лена on 01.02.2024.
//

#ifndef operations_h
#define operations_h

#include <stdio.h>

#include "bool_vector.h"

int operation_num (char* c);
enum status_codes cacalculate(T_vector** res, char* operator, T_vector* a, T_vector* b);
int calculate_values(int operator_num, int a, int b);

#endif /* operations_h */

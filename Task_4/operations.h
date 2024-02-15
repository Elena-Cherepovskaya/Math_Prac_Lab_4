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
#include "vector_name.h"
#include "custom_string.h"

int operation_num (char* c);
enum status_codes calculate(T_vector_name* res, T_string* operator, T_vector_name* a, T_vector_name* b);
int calculate_values(int operator_num, int a, int b);
bool is_operator(char c);

#endif /* operations_h */

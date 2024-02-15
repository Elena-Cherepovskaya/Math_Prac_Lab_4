//
//  operations.c
//  4
//
//  Created by Лена on 01.02.2024.
//

#include "operations.h"
#include "bool_vector.h"
#include "vector_name.h"
#include "transform_x_to_10.h"
#include "status_codes.h"

#include <stdlib.h>
#include <string.h>

int operation_num (char* c)
{
    char* operation_list[] = {"+", "&", "->", "<-", "~", "<>", "+>", "?", "!"};
    
    for (int i = 0; i < 9; ++i)
        if (strcmp(operation_list[i], c) == 0)
            return i;
    return 9;
}

enum status_codes cacalculate(T_vector** res, char* operator, T_vector* a, T_vector* b)
{
    if (*res != NULL || a == NULL || b == NULL)
        return fsc_invalid_parameter;
    
    *res = (T_vector*)malloc(sizeof(T_vector));
    if (*res == NULL)
        return fsc_memory_error_detected;
    
    int num = operation_num(operator);
    switch (num)
    {
        case 0:
            (*res)->data = a->data | b->data;
            break;
        case 1:
            (*res)->data = a->data & b->data;
            break;
        //-> - оператор логической импликации
        case 2:
            (*res)->data = a->data <= b->data;
            break;
        // <-
        case 3:
            (*res)->data = !(a->data <= b->data);
            break;
        case 4:
            (*res)->data = a->data == b->data;
            break;
        case 5:
            (*res)->data = (a->data == 1) ^ (b->data == 0);
            break;
        // +>
        case 6:
            (*res)->data = (a->data == 1) && (b->data == 0);
            break;
        case 7:
            (*res)->data = !((a->data == 1) && (b->data == 1));
            break;
        case 8:
            (*res)->data = ((a->data == 0) && (b->data == 0));
            break;
        default:
            break;
    }
    
    return fsc_ok;
}

int calculate_values(int operator_num, int a, int b)
{
    switch (operator_num)
    {
        case 0:
            return a | b;
        case 1:
            return a & b;
        //-> - оператор логической импликации
        case 2:
            return a <= b;
        // <-
        case 3:
            return !(a <= b);
        case 4:
            return a == b;
        case 5:
            return (a == 1) ^ (b == 0);
        // +>
        case 6:
            return (a == 1) && (b == 0);
            break;
        case 7:
            return !((a == 1) && (b == 1));
            break;
        case 8:
            return ((a == 0) && (b == 0));
            break;
        default:
            break;
    }
    return 0;
}

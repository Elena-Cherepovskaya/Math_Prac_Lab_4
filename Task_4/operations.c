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
#include "custom_string.h"

#include <stdlib.h>
#include <string.h>

int operation_num (char* c)
{
    char* operation_list[] = {"+", "&", "->", "<-", "~", "<>", "+>", "?", "!", "\\"};
    
    for (int i = 0; i < 10; ++i)
        if (strcmp(operation_list[i], c) == 0)
            return i;
    return 10;
}

enum status_codes calculate(T_vector_name* res, T_string* operator, T_vector_name* a, T_vector_name* b)
{
    int num = operation_num(operator->data);
    switch (num)
    {
        case 0:
            res->data->data = a->data->data | b->data->data;
            break;
        case 1:
            res->data->data = a->data->data & b->data->data;
            break;
        //-> - оператор логической импликации
        case 2:
            res->data->data = a->data->data <= b->data->data;
            break;
        // <-
        case 3:
            res->data->data = !(a->data->data <= b->data->data);
            break;
        case 4:
            res->data->data = a->data->data == b->data->data;
            break;
        case 5:
            res->data->data = (a->data->data == 1) ^ (b->data->data == 0);
            break;
        // +>
        case 6:
            res->data->data = (a->data->data == 1) & (b->data->data == 0);
            break;
        case 7:
            res->data->data = !((a->data->data == 1) & (b->data->data == 1));
            break;
        case 8:
            res->data->data = ((a->data->data == 0) & (b->data->data == 0));
            break;
        case 9:
            res->data->data = ~(b->data->data);
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

bool is_operator(char c)
{
    char* list = "+&-><~?!\\";
    int l = (int)strlen(list);
    
    for (int i = 0; i < l; ++i)
        if (c == list[i])
            return true;
    
    return false;
}

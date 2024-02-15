//
//  postfix_transformation.c
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#include "postfix_transformation.h"
#include "status_codes.h"
#include "stack_operation.h"
#include "operations.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum status_codes to_postfix(char** res_buffer, char* buffer)
{
    enum status_codes res = fsc_ok;
    
    if (*res_buffer != NULL || buffer == NULL)
        return fsc_invalid_parameter;

    *res_buffer = malloc(sizeof(char) * strlen(buffer));
    
    if (*res_buffer == NULL)
        return fsc_memory_error_detected;
    
    char* p_res_buffer = *res_buffer;
    char* p_buffer = buffer;
    
    T_stack_operation* stack = NULL;
    while(*p_buffer != 0)
    {
        if (*p_buffer == '>')
            ++p_buffer;
        
        if (isalnum(*p_buffer))
        {
            *p_res_buffer = *p_buffer;
            ++p_res_buffer;
            ++p_buffer;
            continue;
        }
        
        if (*p_buffer == '(')
        {
            res = push_operation(&stack, *p_buffer);
            ++p_buffer;
            continue;
        }
        
        int test_operation = get_operation_num(*p_buffer);
        int test_priority = get_priority(test_operation);
        int top;
        
        if (*p_buffer == ')')
        {
            while(!(is_empty_operation(stack)))
            {
                top_operation(stack, &top);
                if (top == '(')
                {
                    pop_operation(stack, &top);
                    break;
                }
                else
                {
                    pop_operation(stack, &top);
                    *p_res_buffer = num_to_operation(top);
                    ++p_res_buffer;
                }
            }
            ++p_buffer;
            continue;
        }
        
        if (is_empty_operation(stack))
        {
            res = push_operation(&stack, get_operation_num(*p_buffer));
            ++p_buffer;
            continue;
        }
        
        while(!(is_empty_operation(stack)))
        {
            top_operation(stack, &top);
            if ((get_priority(top) >= test_priority) && (num_to_operation(top) != '('))
            {
                int cur_operation;
                pop_operation(stack, &cur_operation);
                
                *p_res_buffer = num_to_operation(cur_operation);
                ++p_res_buffer;
            }
            break;
        }
        res = push_operation(&stack, test_operation);
        
        ++p_buffer;
    }
    
    while (!(is_empty_operation(stack)))
    {
        int cur_operation;
        pop_operation(stack, &cur_operation);
        
        *p_res_buffer = num_to_operation(cur_operation);
        ++p_res_buffer;
    }
    
    *p_res_buffer = 0;
    
    return fsc_ok;
}

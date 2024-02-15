//
//  stack_operation.c
//  4_6
//
//  Created by Лена on 01.02.2024.
//
#define START_CAPACITY 32

#include "stack_operation.h"
#include "status_codes.h"

#include <stdio.h>
#include <stdlib.h>

void clear_stack_operation(T_stack_operation** stack)
{
    if (*stack != NULL)
    {
        if ((*stack)->data != NULL)
        {
            free((*stack)->data);
            (*stack)->data = NULL;
        }
        
        free(*stack);
        *stack = NULL;
    }
}
enum status_codes push_operation(T_stack_operation** stack, int c)
{
    if (*stack == NULL)
    {
        *stack = malloc(sizeof(T_stack_operation));
        if (*stack == NULL)
            return fsc_memory_error_detected;
        
        (*stack)->data = malloc(sizeof(int) * START_CAPACITY);
        if ((*stack)->data == NULL)
        {
            free(*stack);
            *stack = NULL;
            return fsc_memory_error_detected;
        }
        
        (*stack)->capacity = START_CAPACITY;
        (*stack)->len = 0;
    }
    
    if ((*stack)->len == (*stack)->capacity)
    {
        int* tmp_p = realloc((*stack)->data, sizeof(int) * (*stack)->capacity * 2);
        if (tmp_p == NULL)
        {
            clear_stack_operation(stack);
            return fsc_memory_error_detected;
        }
        
        (*stack)->data = tmp_p;
        (*stack)->capacity *= 2;
    }
    
    int index = (*stack)->len;
    ((*stack)->data)[index] = c;
    ++((*stack)->len);
    
    return fsc_ok;
}

enum status_codes top_operation(T_stack_operation* stack, int* res)
{
    if (stack == NULL)
        return fsc_invalid_parameter;
    
    *res = (stack->data)[stack->len - 1];
    
    return fsc_ok;
}

enum status_codes pop_operation(T_stack_operation* stack, int* res)
{
    if (stack == NULL)
        return fsc_invalid_parameter;
    
    *res = (stack->data)[stack->len - 1];
    --(stack->len);
    
    return fsc_ok;
}

void print_stack_operation(T_stack_operation* stack)
{
    for (int i = 0; i < stack->len; ++i)
        printf("%d ", (stack->data)[i]);
    printf("\n");
}

bool is_empty_operation(T_stack_operation* stack)
{
    if (stack == NULL || stack->len == 0)
        return true;
    return false;
}

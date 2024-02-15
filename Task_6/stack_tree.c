//
//  stack_tree.c
//  4_6
//
//  Created by Лена on 01.02.2024.
//
#define START_CAPACITY 32

#include "stack_tree.h"
#include "tree.h"
#include "status_codes.h"

#include <stdlib.h>

void clear_stack_tree(T_stack_tree** stack)
{
    if (*stack != NULL)
    {
        for (int i = 0; i < (*stack)->len; ++i)
        {
            free(((*stack)->data)[i]);
            ((*stack)->data)[i] = NULL;
        }
        
        free((*stack)->data);
        (*stack)->data = NULL;
        
        free(*stack);
        *stack = NULL;
    }
}

enum status_codes push_tree(T_stack_tree** stack, T_node* node)
{
    if (node == NULL)
        return fsc_invalid_parameter;
    
    if (*stack == NULL)
    {
        *stack = malloc(sizeof(T_stack_tree));
        if (*stack == NULL)
            return fsc_memory_error_detected;
        
        (*stack)->data = malloc(sizeof(T_node*) * START_CAPACITY);
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
        T_node** tmp_p = realloc((*stack)->data, sizeof(T_node*) * (*stack)->capacity * 2);
        if (*tmp_p == NULL)
        {
            clear_stack_tree(stack);
            return fsc_memory_error_detected;
        }
        
        (*stack)->data = tmp_p;
        (*stack)->capacity *= 2;
    }
    
    ((*stack)->data)[(*stack)->len] = node;
    ++((*stack)->len);
    
    return fsc_ok;
}

enum status_codes pop_tree(T_stack_tree* stack, T_node** res_node)
{
    if (stack == NULL || stack->len == 0)
        return fsc_invalid_parameter;
    
    --(stack->len);
   *res_node = ((stack->data)[stack->len]);
    
    return fsc_ok;
}

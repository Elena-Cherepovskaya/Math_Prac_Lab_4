//
//  postfix_buffer.c
//  5_list
//
//  Created by Лена on 24.01.2024.
//

#include "postfix_buffer.h"

#include "T_data.h"
#include "status_code.h"

#include <stdlib.h>

#define START_CAPACITY 32

enum status_codes create_postfix_buffer(T_postfix_buffer** postfix_buffer)
{
    if (*postfix_buffer != NULL)
        return fsc_invalid_parameter;
    
    *postfix_buffer = (T_postfix_buffer*)malloc(sizeof(T_postfix_buffer));
    if (*postfix_buffer == NULL)
        return fsc_memory_error_detected;
    
    (*postfix_buffer)->capacity = START_CAPACITY;
    (*postfix_buffer)->data = (T_data*)malloc(sizeof(T_data) * (*postfix_buffer)->capacity);
    
    if ((*postfix_buffer)->data == NULL)
    {
        free(*postfix_buffer);
        *postfix_buffer = NULL;
        return fsc_memory_error_detected;
    }
    (*postfix_buffer)->len = 0;
    
    return fsc_ok;
}

void delete_postfix_buffer(T_postfix_buffer** postfix_buffer)
{
    if (*postfix_buffer != NULL)
    {
        free((*postfix_buffer)->data);
        (*postfix_buffer)->data = NULL;
        (*postfix_buffer)->len = 0;
        free(*postfix_buffer);
        *postfix_buffer = NULL;
    }
}

void clear_postfix_buffer(T_postfix_buffer** postfix_buffer)
{
    if (*postfix_buffer != NULL)
        (*postfix_buffer)->len = 0;
}

enum status_codes add_to_postfix_buffer(T_postfix_buffer** postfix_buffer,
                                        bool is_operator, int value, char* operators_list)
{
    if (*postfix_buffer == NULL)
        return fsc_invalid_parameter;
    
    if ((*postfix_buffer)->len == (*postfix_buffer)->capacity)
    {
        (*postfix_buffer)->capacity *= 2;
        T_data* tmp_p = realloc((*postfix_buffer)->data, sizeof(T_data) * (*postfix_buffer)->capacity);
        if (tmp_p == NULL)
        {
            clear_postfix_buffer(postfix_buffer);
            return fsc_memory_error_detected;
        }
        (*postfix_buffer)->data = tmp_p;
    }
    
    int index = (*postfix_buffer)->len;
    if (is_operator)
    {
        ((*postfix_buffer)->data)[index].operator = value;
        ((*postfix_buffer)->data)[index].is_operator = true;
    }
    else
    {
        ((*postfix_buffer)->data)[index].operand = value;
        ((*postfix_buffer)->data)[index].is_operator = false;
    }
    
    (*postfix_buffer)->len += 1;
    
    return fsc_ok;
}

void print_postfix_buffer(T_postfix_buffer* postfix_buffer)
{
    for (int i = 0; i < postfix_buffer->len; ++i)
    {
        if (postfix_buffer->data[i].is_operator)
            printf("%c", postfix_buffer->data[i].operator);
        else
            printf("%d", postfix_buffer->data[i].operand);
    }
    printf("\n");
}


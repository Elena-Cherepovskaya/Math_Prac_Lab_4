//
//  variables_count.c
//  4_6
//
//  Created by Лена on 01.02.2024.
//
#define START_CAPACITY 32

#include "variables_count.h"
#include "status_codes.h"

#include <ctype.h>
#include <stdlib.h>

int variables_number(char* buffer)
{
    int count = 0;
    char* p_buffer = buffer;
    while (*p_buffer != 0)
        if (isalpha(*p_buffer))
            ++count;
    return count;
}

void clear_list(T_list** list)
{
    if (*list != NULL)
    {
        if ((*list)->data != NULL)
        {
            free((*list)->data);
            (*list)->data = NULL;
        }
        
        if ((*list)->value != NULL)
        {
            free((*list)->value);
            (*list)->value = NULL;
        }
        
        free(*list);
        *list = NULL;
    }
}

int get_value(T_list* list, char letter)
{
    for (int i = 0; i < list->len; ++i)
    {
        if ((list->data)[i] == letter)
            return (list->value)[i];
    }
    return 0;
}

bool is_value_in_list(T_list* list, char n)
{
    for (int i = 0; i < list->len; ++i)
        if ((list->data)[i] == n)
            return true;
    return false;
}

enum status_codes create_list(T_list** list)
{
    if (*list != NULL)
        return fsc_invalid_parameter;
    
    *list = malloc(sizeof(T_list));
    if (*list == NULL)
        return fsc_memory_error_detected;
    (*list)->data = malloc(sizeof(char) * START_CAPACITY);
    if ((*list)->data == NULL)
    {
        free(*list);
        *list = NULL;
        return fsc_invalid_parameter;
    }
    
    (*list)->capacity = START_CAPACITY;
    (*list)->len = 0;
    
    (*list)->value = NULL;
    
    return fsc_ok;
}

enum status_codes add_to_list(T_list** list, char n)
{
    if (*list == NULL)
    {
        *list = malloc(sizeof(T_list));
        if (*list == NULL)
            return fsc_memory_error_detected;
        (*list)->data = malloc(sizeof(char) * START_CAPACITY);
        if ((*list)->data == NULL)
        {
            free(*list);
            *list = NULL;
            return fsc_invalid_parameter;
        }
        
        (*list)->capacity = START_CAPACITY;
        (*list)->len = 0;
        
        (*list)->value = NULL;
    }
    
    if ((*list)->len == (*list)->capacity)
    {
        char* tmp_p = realloc((*list)->data, sizeof(char) * (*list)->capacity * 2);
        if (tmp_p == NULL)
        {
            clear_list(list);
            return  fsc_memory_error_detected;
        }
        (*list)->data = tmp_p;
        (*list)->capacity *= 2;
    }
    
    if (!(is_value_in_list(*list, n)))
    {
        ((*list)->data)[(*list)->len] = n;
        ++((*list)->len);
    }
    
    return fsc_ok;
}

bool is_list_ready(T_list* list)
{
    for (int i = 0; i < list->len; ++i)
        if ((list->value)[i] == 0)
            return false;
    return true;
}

enum status_codes list_generation(T_list* list)
{
    if (list->value == NULL)
    {
        list->value = malloc(sizeof(int) * list->len);
        if (list->value == NULL)
        {
            clear_list(&list);
            return fsc_memory_error_detected;
        }
        
        for (int i = 0; i < list->len; ++i)
        {
            (list->value)[i] = 0;
        }
        
        return fsc_ok;
    }
    
    if (is_list_ready(list))
        return fsc_list_is_ready;
    
    for (int i = 0; i < list->len; ++i)
    {
        if ((list->value)[i] == 0)
        {
            (list->value)[i] = 1;
            return fsc_ok;
        }
        else
        {
            (list->value)[i] = 0;
        }
    }
    
    return fsc_ok;
}

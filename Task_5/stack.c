//
//  stack.c
//  5_list
//
//  Created by Лена on 24.01.2024.
//
#include "stack.h"

#include "T_data.h"
#include "status_code.h"

#include <stdlib.h>
#include <stdbool.h>

enum status_codes clear_stack(T_node** head)
{
    if (*head == NULL)
        return fsc_invalid_parameter;
    
    T_node* next_node = *head;
    T_node* cur_node = NULL;
    while(next_node != NULL)
    {
        cur_node = next_node;
        next_node = next_node->p_next;
        free(cur_node);
        cur_node = NULL;
    }
    
    return fsc_ok;
}

enum status_codes push(T_node** head, bool is_operator, int value, char* operators_list)
{
    //Стек еще не был создан
    if (*head == NULL)
    {
        *head = (T_node*)malloc(sizeof(T_node));
        if (*head == NULL)
            return fsc_memory_error_detected;
        
        if (is_operator)
        {
            (*head)->data.operator = value;
            (*head)->data.is_operator = true;
        }
        else
        {
            (*head)->data.operand = value;
            (*head)->data.is_operator = false;
        }
        
        (*head)->p_next = NULL;
    }
    //Стек уже создан
    else
    {
        T_node* cur_node = *head;
        while(true)
        {
            if (cur_node->p_next == NULL)
            {
                cur_node->p_next = (T_node*)malloc(sizeof(T_node));
                if (cur_node->p_next == NULL)
                    return fsc_memory_error_detected;
                
                cur_node =cur_node->p_next;
                if (is_operator)
                {
                    cur_node->data.operator = value;
                    cur_node->data.is_operator = true;
                }
                else
                {
                    cur_node->data.operand = value;
                    cur_node->data.is_operator = false;
                }
                cur_node->p_next = NULL;
                break;
            }
            else
                cur_node = cur_node->p_next;
        }
    }
    
    return fsc_ok;
}

enum status_codes pop(T_node** head, T_node* last_node)
{
    if (*head == NULL)
        return fsc_memory_error_detected;
    
    T_node* prev_node = NULL;
    T_node* cur_nude = *head;
    while(cur_nude->p_next != NULL)
    {
        prev_node = cur_nude;
        cur_nude = cur_nude->p_next;
    }
    
    if (prev_node == NULL)
    {
        *last_node = *cur_nude;
        free(cur_nude);
        *head = NULL;
    }
    else
    {
        *last_node = *cur_nude;
        free(cur_nude);
        prev_node->p_next = NULL;
    }
    
    return  fsc_ok;
}
 
bool is_stack_empty(T_node* head)
{
    return (head == NULL);
}

int stack_len(T_node* head)
{
    if (head == NULL)
        return 0;
    
    int len = 0;
    T_node* current_node = head;
    while(current_node != NULL)
    {
        ++len;
        current_node = current_node->p_next;
    }
    
    return len;
}

//
//  stack.h
//  5_list
//
//  Created by Лена on 24.01.2024.
//

#ifndef stack_h
#define stack_h

#include "T_data.h"

typedef struct
{
    T_data data;
    void* p_next;
} T_node;

enum status_codes pop(T_node** head, T_node* last_node);
enum status_codes push(T_node** head, bool is_operator, int value, char* operators_list);
bool is_stack_empty(T_node* head);
int stack_len(T_node* head);
enum status_codes clear_stack(T_node** head);

#endif /* stack_h */

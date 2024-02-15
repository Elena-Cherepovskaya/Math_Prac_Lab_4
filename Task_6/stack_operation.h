//
//  stack_operation.h
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#ifndef stack_operation_h
#define stack_operation_h

#include <stdbool.h>

// Стек операций
typedef struct
{
    int* data;
    int len;
    int capacity;
}T_stack_operation;

void clear_stack_operation(T_stack_operation** stack);
enum status_codes push_operation(T_stack_operation** stack, int c);
enum status_codes top_operation(T_stack_operation* stack, int* res);
enum status_codes pop_operation(T_stack_operation* stack, int* res);
void print_stack_operation(T_stack_operation* stack);
bool is_empty_operation(T_stack_operation* stack);

#endif /* stack_operation_h */

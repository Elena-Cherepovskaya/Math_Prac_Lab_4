//
//  stack_tree.h
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#ifndef stack_tree_h
#define stack_tree_h

#include "tree.h"

typedef struct
{
    T_node** data;
    int len;
    int capacity;
}T_stack_tree;

void clear_stack_tree(T_stack_tree** stack);
enum status_codes push_tree(T_stack_tree** stack, T_node* node);
enum status_codes pop_tree(T_stack_tree* stack, T_node** res_node);

#endif /* stack_tree_h */

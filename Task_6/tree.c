//
//  tree.c
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#include "tree.h"

#include "status_codes.h"
#include "char_num_transformation.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

enum status_codes create_node(T_node** res_node, char c)
{
    if (*res_node != NULL)
        return fsc_invalid_parameter;
    
    *res_node = malloc(sizeof(T_node));
    if (*res_node == NULL)
        return fsc_memory_error_detected;
    
    (*res_node)->data = c;
    (*res_node)->p_left = NULL;
    (*res_node)->p_right = NULL;
    
    return fsc_ok;
}

void print_tree(T_node* current_node, int count)
{
    for (int i = 0; i < count; ++i)
        printf(" ");
    printf("%c\n", current_node->data);
    
    if (current_node->p_left != NULL)
        print_tree(current_node->p_left, count + 1);
        
    if (current_node->p_right != NULL)
        print_tree(current_node->p_right, count + 1);
}

void clear_tree(T_node** current_node)
{
    if ((*current_node)->p_left != NULL)
        clear_tree((T_node**)&((*current_node)->p_left));
    
    if ((*current_node)->p_right != NULL)
        clear_tree((T_node**)&((*current_node)->p_right));
    
    free(*current_node);
    *current_node = NULL;
}

enum status_codes type_of_node(T_node* node)
{
    if (node == NULL)
        return fsc_NULL;
    
    if (isalpha(node->data))
        return fsc_letter;
    
    if (isnumber(node->data))
        return fsc_number;
    
    return fsc_operator;
}

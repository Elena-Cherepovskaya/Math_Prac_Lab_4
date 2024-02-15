//
//  tree_calculation.c
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#include "tree_calculation.h"
#include "char_num_transformation.h"
#include "operations.h"

#include <stdlib.h>
#include <ctype.h>

enum status_codes create_values_tree(T_node** new_current_node, T_node* current_node, T_list* list)
{
    *new_current_node = malloc(sizeof(T_node));
    if (*new_current_node == NULL)
    {
        //clear
        return fsc_memory_error_detected;
    }
    
    if (isalpha(current_node->data))
        (*new_current_node)->data = num_to_char(get_value(list, current_node->data));
    else
        (*new_current_node)->data = current_node->data;
    
    (*new_current_node)->p_left = NULL;
    (*new_current_node)->p_right = NULL;
    
    
    if (current_node->p_left != NULL)
        create_values_tree((T_node**)&((*new_current_node)->p_left), current_node->p_left, list);
    
    if (current_node->p_right != NULL)
        create_values_tree((T_node**)&((*new_current_node)->p_right), current_node->p_right, list);
    
    return fsc_ok;
}

enum status_codes calculate_tree(T_node** current_node, T_list* list)
{
    if ((*current_node)->p_left != NULL)
        calculate_tree((T_node**)&((*current_node)->p_left), list);
    
    if ((*current_node)->p_right != NULL)
        calculate_tree((T_node**)&((*current_node)->p_right), list);
    
    enum status_codes type_of_p_left = type_of_node((*current_node)->p_left);
    enum status_codes type_of_p_right = type_of_node((*current_node)->p_right);
    
    if ((type_of_p_left == fsc_number) && (type_of_p_right == fsc_NULL))
    {
        T_node* a = (*current_node)->p_left;
        int tmp_res = cacalculate((*current_node)->data, a->data, 0);
        
        free((*current_node)->p_left);
        (*current_node)->p_left = NULL;
        
        (*current_node)->data = tmp_res;
    }
    else
        if ((type_of_p_left == fsc_number) && (type_of_p_right == fsc_number))
        {
            T_node* a = (*current_node)->p_left;
            T_node* b = (*current_node)->p_right;
            char tmp_res = cacalculate((*current_node)->data, a->data, b->data);
            
            free((*current_node)->p_left);
            (*current_node)->p_left = NULL;
            free((*current_node)->p_right);
            (*current_node)->p_right = NULL;
            
            (*current_node)->data = tmp_res;
            
            return fsc_ok;
        }
    
    return fsc_ok;
}

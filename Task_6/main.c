//
//  main.c
//  4_6
//
//  Created by Лена on 31.12.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "status_codes.h"
#include "postfix_transformation.h"
#include "stack_tree.h"
#include "tree.h"
#include "operations.h"
#include "variables_count.h"
#include "file_generation.h"
#include "tree_calculation.h"

#define START_CAPACITY 32


int main(int argc, const char * argv[])
{
    enum status_codes res = fsc_ok;
    
    if (argc < 2)
        res = fsc_invalid_parameter;
    
    FILE* file_input = NULL;
    if (res == fsc_ok)
    {
        file_input = fopen(argv[1], "r");
        if (file_input == NULL)
            res = fsc_file_is_not_found;
    }
    
    char* buffer = NULL;
    size_t size;
    if (res == fsc_ok)
        getline(&buffer, &size, file_input);
        
    char* postfix_buffer = NULL;
    if (res == fsc_ok)
    {
        res = to_postfix(&postfix_buffer, buffer);
        printf("%s\n", postfix_buffer);
    }

    
    char* p_postfix_buffer = postfix_buffer;
    T_stack_tree* stack_tree = NULL;
    
    if (res == fsc_ok)
    {
        while(*p_postfix_buffer != 0)
        {
            if (isalnum(*p_postfix_buffer))
            {
                T_node* node = NULL;
                res = create_node(&node, *p_postfix_buffer);
                if (res != fsc_ok)
                    break;
                
                res = push_tree(&stack_tree, node);
                if (res != fsc_ok)
                    break;
            }
            else
            {
                int num = operands_number(*p_postfix_buffer);
                
                switch (num)
                {
                    case 1:
                    {
                        T_node* new_node = NULL;
                        res = create_node(&new_node, *p_postfix_buffer);
                        
                        if (res == fsc_ok)
                            res = pop_tree(stack_tree, (T_node**)&(new_node->p_left));
                        
                        if (res == fsc_ok)
                            res = push_tree(&stack_tree, new_node);
                        break;
                    }
                    case 2:
                    {
                        T_node* new_node = NULL;
                        res = create_node(&new_node, *p_postfix_buffer);
                        
                        if (res == fsc_ok)
                            res = pop_tree(stack_tree, (T_node**)&(new_node->p_right));
                        
                        if (res == fsc_ok)
                            res = pop_tree(stack_tree, (T_node**)&(new_node->p_left));
                        
                        if (res == fsc_ok)
                            res = push_tree(&stack_tree, new_node);
                        
                        break;
                    }
                    default:
                        break;
                }
                
                if (res != fsc_ok)
                    break;
            }
            ++p_postfix_buffer;
        }
    }
    
    if (res == fsc_ok)
        print_tree((stack_tree->data)[0], 0);
    
    
    T_list* nodes_list = NULL;
    p_postfix_buffer = postfix_buffer;
    if (res == fsc_ok)
        res = create_list(&nodes_list);
    
    if (res == fsc_ok)
    {
        while(*p_postfix_buffer != 0)
        {
            if (isalpha(*p_postfix_buffer))
                res = add_to_list(&nodes_list, *p_postfix_buffer);
            ++p_postfix_buffer;
            
            if (res != fsc_ok)
                break;
        }
    }
    printf("\n");
    
    char* file_output_name = NULL;
    if (res == fsc_ok)
        res = generate_output_file(&file_output_name, argv[1], 3);
    //printf("%s\n", file_output_name);

    FILE*  file_output = NULL;
    if (res == fsc_ok)
    {
        file_output = fopen(file_output_name, "w");
        if (file_output == NULL)
            res = fsc_memory_error_detected;
    }
    
    if (res == fsc_ok)
    {
        //печать подписей столбцов
        for (int i = 0; i < nodes_list->len; ++i)
            fprintf(file_output, "%c ", (nodes_list->data)[i]);
        fprintf(file_output, "\n");
        
        while (true)
        {
            res = list_generation(nodes_list);
            if (res == fsc_list_is_ready)
                break;
            
            //печать 0 и 1
            for (int i = 0; i < nodes_list->len; ++i)
                fprintf(file_output, "%d ", (nodes_list->value)[i]);
                
            
            T_node* new_root = NULL;
            res = create_values_tree(&new_root, (stack_tree->data)[0], nodes_list);
            
            if (res != fsc_ok)
                break;
            
            res = calculate_tree(&new_root, nodes_list);
            if (res != fsc_ok)
                break;
            
            fprintf(file_output, " %c\n", new_root->data);
            clear_tree(&new_root);
        }
    }
    
    
    if (file_input != NULL)
        fclose(file_input);
    if (file_output != NULL)
        fclose(file_output);
    
    return 0;
}

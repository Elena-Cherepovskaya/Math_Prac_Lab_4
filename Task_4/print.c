//
//  print.c
//  4
//
//  Created by Лена on 05.02.2024.
//

#include "print.h"
#include "status_codes.h"
#include "operations.h"
#include "custom_string.h"
#include "bool_vector.h"
#include "vector_name.h"
#include "vector_storage.h"
#include "transform_x_to_10.h"

#include <string.h>
#include <stdlib.h>
/*
enum status_codes print(T_string* command, T_vector_storage* vector_storage, char A, char B, char C, int base)
{
    enum status_codes res = fsc_ok;
    
    int command_num = operation_num(command->data);
    
    if (command_num == 9)
    {
        if (strcmp(command->data, "read") == 0)
            command_num = 10;
        else
        {
            if (strcmp(command->data, "write") == 0)
                command_num = 11;
            else
                res = fsc_syntax_error;
        }
    }
    
    T_vector_name* vector_name_A = NULL;
    T_vector* vector_B = NULL;
    T_vector* vector_C = NULL;
    
    if ((command_num >= 0) && (command_num <= 8))
    {
        res = find_vector_in_storage(&vector_B, vector_storage, B);
        if (res == fsc_vector_is_not_found)
            res = fsc_semantic_error;
        
        if (res == fsc_ok)
            res = find_vector_in_storage(&vector_C, vector_storage, C);
        if (res == fsc_vector_is_not_found)
            res = fsc_semantic_error;
        
        if (res == fsc_ok)
        {
            if (is_vector_in_storage(vector_storage, A))
                res = change_vactor_in_storage(vector_storage, A, calculate_values(command_num, vector_B->data, vector_C->data));
            else
            {
                res = create_vector_name(&vector_name_A, A, calculate_values(command_num, vector_B->data, vector_C->data));
                res = add_to_vector_starage(&vector_storage, vector_name_A);
            }
        }
    }
    
    if (command_num == 9)
    {
        res = find_vector_in_storage(&vector_B, vector_storage, B);
        if (res == fsc_vector_is_not_found)
            res = fsc_semantic_error;
        
        if (res == fsc_ok)
        {
            if (is_vector_in_storage(vector_storage, A) == fsc_is_detected)
                res = change_vactor_in_storage(vector_storage, A, !(vector_B->data));
            else
            {
                res = create_vector_name(&vector_name_A, A, !(vector_B->data));
                res = add_to_vector_starage(&vector_storage, vector_name_A);
            }
        }
    }
    
    if (command_num == 10)
    {
        char buf[BUFSIZ];
        printf("enter a number in the %d number system ", base);
        scanf("%s", buf);
        
        int value_10 = 0;
        res = transform_x_to_10(&value_10, buf, base);
        
        if (is_vector_in_storage(vector_storage, A) == fsc_is_detected)
            res = change_vactor_in_storage(vector_storage, A, value_10);
        else
        {
            res = create_vector_name(&vector_name_A, A, value_10);
            res = add_to_vector_starage(&vector_storage, vector_name_A);
        }
    }
    
    if (command_num == 11)
    {
        if (is_vector_in_storage(vector_storage, A) == fsc_is_detected)
        {
            find_vector_in_storage(&vector_B, vector_storage, A);
            char* buf = NULL;
            res = transform_10_to_x(&buf, vector_B->data, base);
            printf("%s\n", buf);
            free(buf);
            buf = NULL;
        }
        
    }
    
    print_vector_storage(stdout, vector_storage);
    fprintf(stdout, "\n");
    
    if (vector_B != NULL)
        clear_vector(&vector_B);
    if (vector_C != NULL)
        clear_vector(&vector_C);
    
    return fsc_ok;
}
*/
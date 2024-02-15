//
//  main.c
//  4
//
//  Created by Лена on 01.02.2024.
//

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "transform_x_to_10.h"
#include "status_codes.h"
#include "bool_vector.h"
#include "operations.h"
#include "vector_name.h"
#include "vector_storage.h"
#include "custom_string.h"
#include "print.h"

enum state
{
    initialize,
    find_command_or_variable,
    command_read_let,
    command_read_X,
    command_read_action,
    command_read_Y,
    command_read_find_variable,
    command_read_ready,
    command_write_find_variable,
    command_write_ready,
    command_end
};

int main(int argc, const char * argv[])
{
    enum status_codes res = fsc_ok;
    
    bool is_trace = false;
    if (argc < 2)
        res = fsc_invalid_parameter;
    else
    {
        if ((argc == 4) && (strcmp(argv[2], "/trace") == 0))
            is_trace = true;
    }
    
    FILE* file_input = NULL;
    if (res == fsc_ok)
    {
        file_input = fopen(argv[1], "r");
        if (file_input == NULL)
            res = fsc_file_is_not_found;
    }
    
    FILE* file_output = stdout;
    if ((res == fsc_ok) && (is_trace))
    {
        file_output = fopen(argv[3], "w");
        if (file_output == NULL)
            res = fsc_file_is_not_found;
    }
    
    T_vector_storage* vector_storage = NULL;
    if (res == fsc_ok)
        res = create_vector_storage(&vector_storage);
    
    enum state current_state = initialize;
    bool skip_separator = true;
    bool read_argument = true;
    bool read_value = false;
    bool read_action = false;
    char skip_char = 0;

    char input_buffer[BUFSIZ];

    T_string * str_value = NULL;    // Читаем числа
    T_string * str_argument = NULL; // Читаем текст
    T_string * str_action = NULL;
    
    if (res == fsc_ok)
        res = create_string(&str_argument);
    
    if (res == fsc_ok)
        res = create_string(&str_value);
    
    if (res == fsc_ok)
        res = create_string(&str_action);
    
    T_vector_name *x = NULL;
    T_vector_name *y = NULL;
    T_vector_name *result = NULL;
    
    bool rem_normal = false;// {}
    bool rem_line = false;// %
    
    if (res == fsc_ok)
    {
        bool is_file_finish = false;
        char c = 0;
        bool repeat = false;
        while (true)
        {
            if (is_file_finish)
                break;
            if (!(repeat))
            {
                if ((c = fgetc(file_input)) == EOF)
                    is_file_finish = true;
            }
            
            if (res != fsc_ok)
                break;
            
            
            repeat = false;

            if (current_state == initialize)
            {
                clear_string(str_argument);
                skip_separator = true;
                read_argument = true;
                read_value = false;
                read_action = false;
                current_state = find_command_or_variable;
            }
            
            bool prev_rem = rem_line || rem_normal;
            
            rem_line |= (c == '%');
            rem_line ^= (rem_line && (c == '\n'));
            rem_normal |= (c == '{');
            rem_normal ^= (rem_normal && (c == '}'));
                                        
            if (prev_rem || rem_line || rem_normal)
                continue;

            if (c <= 32)
                continue;

            //();,
            if (skip_separator)
            {
                if ((c != ' ') && (c != '\t') && (c != '\n') && (c != '\r') && (c != skip_char))
                {
                    skip_char = 0;
                    skip_separator = false;
                }
                else
                    continue;
            }

            if (read_argument)
            {
                if (((c >= 'a') && (c <= 'z')) ||
                    ((c >= 'A') && (c <= 'Z')))
                {
                    res = add_to_string(str_argument, c);
                    if (res != fsc_ok)
                        break;
                    
                    continue;
                }
                else
                {
                    if (str_argument->len == 0)
                    {
                        res = fsc_syntax_error;
                        break;
                    }
                    
                    read_argument = false;
                    repeat = true;
                }
            }

            if (read_value)
            {
                if ((c >= '0') && (c <= '9'))
                {
                    res = add_to_string(str_value, c);
                    if (res != fsc_ok)
                        break;
                    continue;
                }
                else
                {
                    if (str_value->len == 0)
                    {
                        res = fsc_syntax_error;
                        break;
                    }
                    
                    if (res != fsc_ok)
                        break;
                    
                    read_value = false;
                    repeat = true;
                }
            }
            
            if (read_action)
            {
                if (is_operator(c) || (c == ':') || (c == '='))
                {
                    res = add_to_string(str_action, c);
                    if (res != fsc_ok)
                        break;
                    
                    continue;
                }
                else
                {
                    if (str_action->len == 0)
                        res = fsc_syntax_error;
                    if(res != fsc_ok)
                        break;
                    
                    read_action = false;
                    repeat = true;
                }
            }
            
            switch (current_state)
            {
                case find_command_or_variable:
                {
                    if (str_argument->len > 1)
                    {
                        skip_separator = true;
                        skip_char = '(';
                        read_argument = true;
                        if (string_comp(str_argument, "read"))
                            current_state = command_read_find_variable;
                        else
                        {
                            if (string_comp(str_argument, "write"))
                                current_state = command_write_find_variable;
                            else
                            {
                                res = fsc_syntax_error;
                                break;
                            }
                        }
                        clear_string(str_argument);
                    }
                    else
                    {
                        if (str_argument->len == 1)
                        {
                            result = NULL;
                            res = vector_storage_get_vector(vector_storage, str_argument->data[0], &result);
                            
                            
                            if (res == fsc_is_not_detected)
                            {
                                vector_storage_set_vector(vector_storage, str_argument->data[0], 0);
                                res = vector_storage_get_vector(vector_storage, str_argument->data[0], &result);
                                
                                print_vector_storage(vector_storage, file_output);
                                fprintf(file_output, "\n");
                            }
                            if (res == fsc_ok)
                            {
                                skip_separator = true;
                                read_action = true;
                                clear_string(str_action);
                                current_state = command_read_let;
                            }
                        }
                        else
                        {
                            res = fsc_syntax_error;
                            break;
                        }
                    }
                    break;
                }
                    
                case command_read_let:
                    if (string_comp(str_action, ":="))
                    {
                        current_state = command_read_X;
                        clear_string(str_argument);
                        read_argument = true;
                        skip_separator = true;
                        break;
                    }
                    
                    if (string_comp(str_action, ":=\\"))
                    {
                        current_state = command_read_Y;
                        clear_string(str_argument);
                        clear_string(str_action);
                        res = add_to_string(str_action, '\\');
                        if (res != fsc_ok)
                            break;
                        
                        read_argument = true;
                        skip_separator = true;
                        break;
                    }
                    
                    res = fsc_syntax_error;
                    break;
                                        
                case command_read_X:
                    x = NULL;
                    res = vector_storage_get_vector(vector_storage, str_argument->data[0], &x);
                    if (res != fsc_ok)
                        break;
                    
                    if (res == fsc_ok)
                    {
                        current_state = command_read_action;
                        clear_string(str_action);
                        read_action = true;
                        skip_separator = true;
                    }
                    break;
                    
                case command_read_action:
                    current_state = command_read_Y;
                    clear_string(str_argument);
                    read_argument = true;
                    skip_separator = true;
                    break;
                    
                case command_read_Y:
                    y = NULL;
                    res = vector_storage_get_vector(vector_storage, str_argument->data[0], &y);
                    if (res != fsc_ok)
                        break;
                    
                    if (res == fsc_ok)
                    {
                        res = calculate(result, str_action, x, y);
                        if (res != fsc_ok)
                            break;
                        
                        res = vector_storage_set_vector(vector_storage, result->name, result->data->data);
                        if (res != fsc_ok)
                            break;
                        print_vector_storage(vector_storage, file_output);
                        fprintf(file_output, "\n");
                        
                        current_state = command_end;
                        skip_char = ')';
                        skip_separator = true;
                    }
                    break;

                case command_read_find_variable:
                    skip_separator = true;
                    skip_char = ',';
                    read_value = true;
                    clear_string(str_value);
                    current_state = command_read_ready;
                    break;
                
                case command_write_find_variable:
                    skip_separator = true;
                    skip_char = ',';
                    read_value = true;
                    clear_string(str_value);
                    current_state = command_write_ready;
                    break;

                case command_read_ready:
                {
                    printf("Enter value:");
                    scanf("%s", input_buffer);
                    int base = 0;
                    res = transform_x_to_10(&base, str_value->data, 10);
                    if (res != fsc_ok)
                        break;

                    int v = 0;
                    res = transform_x_to_10(&v, input_buffer, base);
                    if (res != fsc_ok)
                        break;
                    
                    res = vector_storage_set_vector(vector_storage, str_argument->data[0], v);
                    if (res != fsc_ok)
                        break;
                    print_vector_storage(vector_storage, file_output);
                    fprintf(file_output, "\n");
                    
                    current_state = command_end;
                    skip_char = ')';
                    skip_separator = true;
                    break;
                }
                    
                case command_write_ready:
                {
                    T_vector_name *vector = NULL;
                    res = vector_storage_get_vector(vector_storage, str_argument->data[0], &vector);
                    if (res != fsc_ok)
                        break;
                    
                    if (res == fsc_ok)
                    {
                        int base = 0;
                        res = transform_x_to_10(&base, str_value->data, 10);
                        if (res != fsc_ok)
                            break;
                        
                        char *output_buffer = NULL;
                        res = transform_10_to_x(&output_buffer, vector->data->data, base);
                        if (res != fsc_ok)
                            break;
                        
                        fprintf(file_output, "%c = %s\n\n", vector->name, output_buffer);
                        free(output_buffer);
                    }

                    current_state = command_end;
                    skip_char = ')';
                    skip_separator = true;

                    break;
                }
                
                case command_end:
                    if (c == ';')
                    {
                        current_state = initialize;
                    }
                    else
                    {
                        res = fsc_syntax_error;
                    }
                    break;
                    
                default:
                    break;
            }
            
            if (res != fsc_ok)
                break;
        }
    }
    
    switch (res)
    {
        case fsc_syntax_error:
            fprintf(file_output, "syntax error\n");
            break;
        case fsc_is_not_detected:
            fprintf(file_output, "semantic error\n");
            break;
        case fsc_invalid_parameter:
            fprintf(file_output, "runtime error\n");
        default:
            break;
    }
    
    free_string(&str_argument);
    free_string(&str_value);
    free_string(&str_action);
    
    if (file_input != NULL)
        fclose(file_input);
    
    if ((file_output != NULL) && (file_output != stdout))
        fclose(file_output);
    
    if (vector_storage != NULL)
        free_vector_storage(&vector_storage);
    
    return 0;
}

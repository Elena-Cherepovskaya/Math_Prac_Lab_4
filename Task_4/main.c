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
    find_command_or_variable,
    command_read_find_variable,
    command_write_find_variable,
    command_read_ready
};

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
    
    T_vector_storage* vector_storage = NULL;
    if (res == fsc_ok)
        res = create_vector_storage(&vector_storage);
    
    // bool st_separator = true;
    // bool st_read_string = true;
    // T_string* command = NULL;
    // T_string* variable_list = NULL;
    enum state current_state = find_command_or_variable;
    bool skip_separator = true;
    bool read_argument = true;
    bool read_value = false;
    char skip_char = 0;

    char input_buffer[256];

    T_string * str_value = NULL;    // Читаем числа
    T_string * str_argument = NULL; // Читаем текст
    T_string * str_argument_1 = NULL;
    T_string * str_argument_2 = NULL;

    res = create_string(&str_argument);
    res = create_string(&str_argument_1);
    res = create_string(&str_argument_2);
    res = create_string(&str_value);
    if (res == fsc_ok)
    {
        char c;
        while ((c = fgetc(file_input)) != EOF)
        {
            if (c < 32)
                continue;

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
                    continue;
                }
                else
                    read_argument = false;
            }

            if (read_value)
            {
                if ((c >= '0') && (c <= '9'))
                    res = add_to_string(str_value, c);
            }
            
            switch (current_state)
            {
                case find_command_or_variable:
                {
                    if (string_comp(str_argument, "read"))
                    {
                        skip_separator = true;
                        skip_char = '(';
                        read_argument = true;
                        clear_string(str_argument);
                        current_state = command_read_find_variable;
                    }
                    if (string_comp(str_argument, "write"))
                    {
                        skip_separator = true;
                        skip_char = '(';
                        read_argument = true;
                        clear_string(str_argument);
                        current_state = command_write_find_variable;
                    }
                    break;
                }
                case command_read_find_variable:
                    skip_separator = true;
                    skip_char = ',';
                    read_value = true;
                    clear_string(str_value);
                    current_state = command_read_ready;
                    break;
                
                case command_write_find_variable:
                    break;

                case command_read_ready:
                {
                    printf("Enter value:");
                    scanf("%s", input_buffer);
                    int base;
                    transform_x_to_10(&base, str_value->data, 10);

                    int res;
                    transform_x_to_10(&res, input_buffer, base);
                    break;
                }
            }
        }

        free_string(&str_value);
    }
    
    return 0;
}

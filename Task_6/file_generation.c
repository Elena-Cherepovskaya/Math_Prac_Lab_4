//
//  file_generation.c
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#include "file_generation.h"
#include "status_codes.h"

#include <stdlib.h>
#include <string.h>

bool is_leter(void)
{
    return rand() % 2;
}

enum status_codes generate_output_file(char** output_file, const char * input_file, int name_len)
{
    if ((*output_file != NULL) || (input_file == NULL))
        return fsc_invalid_parameter;
    
    int index = (int)strlen(input_file);
    *output_file = malloc(sizeof(char) * (index + name_len));
    if (*output_file == NULL)
        return fsc_memory_error_detected;
    
    while ((input_file[index] != '/') && (index != 0))
        --index;
    ++index;
    
    strcat(*output_file, input_file);
    for (int i = 0; i < name_len; ++i)
    {
        (*output_file)[index] = (rand() % 10 + is_leter()) ? 'a' : '0';
        ++index;
    }
    strcpy(&((*output_file)[index]), ".txt");
    
    return fsc_ok;
}

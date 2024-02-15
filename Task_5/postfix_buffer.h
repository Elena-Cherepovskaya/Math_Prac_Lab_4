//
//  postfix_buffer.h
//  5_list
//
//  Created by Лена on 24.01.2024.
//

#ifndef postfix_buffer_h
#define postfix_buffer_h

#include <stdio.h>

#include "T_data.h"

typedef struct
{
    T_data* data;
    int capacity;
    int len;
} T_postfix_buffer;

enum status_codes create_postfix_buffer(T_postfix_buffer** postfix_buffer);
enum status_codes add_to_postfix_buffer(T_postfix_buffer** postfix_buffer,
                                        bool is_operator, int value, char* operators_list);
void clear_postfix_buffer(T_postfix_buffer** postfix_buffer);

#endif /* postfix_buffer_h */

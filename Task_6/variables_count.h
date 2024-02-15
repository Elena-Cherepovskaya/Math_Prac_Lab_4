//
//  variables_count.h
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#ifndef variables_count_h
#define variables_count_h

#include <stdbool.h>

typedef struct
{
    char* data;
    int* value;
    int len;
    int capacity;
}T_list;

int variables_number(char* buffer);
void clear_list(T_list** list);
int get_value(T_list* list, char letter);
bool is_value_in_list(T_list* list, char n);
enum status_codes add_to_list(T_list** list, char n);
bool is_list_ready(T_list* list);
enum status_codes list_generation(T_list* list);
enum status_codes create_list(T_list** list);

#endif /* variables_count_h */

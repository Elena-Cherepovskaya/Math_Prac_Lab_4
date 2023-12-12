//
//  main.c
//  7
//
//  Created by Лена on 10.12.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>


#define START_CAPACITY 4

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
    fsc_memory_error_detected,
    fsc_is_num,
    fsc_MemoryCell_is_not_found,
    fsc_file_is_not_found,
};

typedef struct
{
    char * name;
    int value;
}T_MemoryCell;

typedef struct
{
    T_MemoryCell** list;
    int len;
    int capacity;
}T_MemoryCell_storage;

enum status_codes create_MemoryCell(T_MemoryCell** MemoryCell,
                                    char const * name, int value)
{
    if ((*MemoryCell != NULL) ||
        (name == NULL))
        return fsc_invalid_parameter;
    
    *MemoryCell = malloc(sizeof(T_MemoryCell));
    if (*MemoryCell == NULL)
        return fsc_memory_error_detected;
    
    (*MemoryCell)->name = malloc(sizeof(char) * (strlen(name) + 1));
    if ((*MemoryCell)->name == NULL)
    {
        free(*MemoryCell);
        *MemoryCell = NULL;
        return fsc_memory_error_detected;
    }
    
    strcpy((*MemoryCell)->name, name);
    (*MemoryCell)->value = value;

    return fsc_ok;
}

enum status_codes create_MemoryCell_storage(T_MemoryCell_storage** MemoryCell_storage)
{
    if (*MemoryCell_storage != NULL)
        return fsc_invalid_parameter;
    
    *MemoryCell_storage = malloc(sizeof(T_MemoryCell_storage));
    if (*MemoryCell_storage == NULL)
        return fsc_memory_error_detected;
    
    (*MemoryCell_storage)->list = malloc(sizeof(T_MemoryCell*) * START_CAPACITY);
    if ((*MemoryCell_storage)->list == NULL)
    {
        free(*MemoryCell_storage);
        return fsc_memory_error_detected;
    }

    (*MemoryCell_storage)->len = 0;
    (*MemoryCell_storage)->capacity = START_CAPACITY;
    
    return fsc_ok;
}

enum status_codes cleare_MemoryCell(T_MemoryCell** MemoryCell)
{
    if (*MemoryCell == NULL)
        return fsc_invalid_parameter;
    
    free((*MemoryCell)->name);
    free(*MemoryCell);
    *MemoryCell =  NULL;
    
    return fsc_ok;
}

enum status_codes clear_MemoryCell_storage(T_MemoryCell_storage** MemoryCell_storage)
{
    if (*MemoryCell_storage == NULL)
        return fsc_invalid_parameter;
    
    for (int i = 0; i < (*MemoryCell_storage)->len; ++i)
        free((*MemoryCell_storage)->list[i]);

    free(*MemoryCell_storage);
    *MemoryCell_storage = NULL;
    
    return fsc_ok;
}


int comp(const void * a, const void * b)
{
    T_MemoryCell* MemoryCell_a = *(T_MemoryCell**)a;
    T_MemoryCell* MemoryCell_b = *(T_MemoryCell**)b;
    
    return strcmp(MemoryCell_a->name, MemoryCell_b->name);
}

enum status_codes add_MemoryCell_to_storage(T_MemoryCell_storage* MemoryCell_storage,
                                            T_MemoryCell * MemoryCell)
{
    if (MemoryCell_storage->len == MemoryCell_storage->capacity)
    {
        MemoryCell_storage->capacity *= 2;
        T_MemoryCell** tmp_p = realloc(MemoryCell_storage->list, sizeof(T_MemoryCell*) * MemoryCell_storage->capacity);
        if (tmp_p == NULL)
            return fsc_memory_error_detected;

        MemoryCell_storage->list = tmp_p;
    }
    
    int ind = MemoryCell_storage->len;
    (MemoryCell_storage->list)[ind] = MemoryCell;
    ++(MemoryCell_storage->len);
    
    qsort(MemoryCell_storage->list, MemoryCell_storage->len, sizeof(T_MemoryCell*), comp);
    return fsc_ok;
}

enum status_codes add_data_to_storage(T_MemoryCell_storage* MemoryCell_storage,
                                      char const * name, int value)
{
    enum status_codes res = fsc_ok;
    
    T_MemoryCell *cell = NULL;
    res = create_MemoryCell(&cell, name, value);
    if (res != fsc_ok)
        return res;
    
    res = add_MemoryCell_to_storage(MemoryCell_storage, cell);
    if (res != fsc_ok)
        cleare_MemoryCell(&cell);
    
    qsort(MemoryCell_storage->list,
          MemoryCell_storage->len,
          sizeof(T_MemoryCell*), comp);

    return res;
}

enum status_codes get_MemoryCell(T_MemoryCell_storage* MemoryCell_stogare,
                                 T_MemoryCell** res_MemoryCell, char const * name)
{
    if (name == NULL)
        return fsc_invalid_parameter;
    
    if (isdigit(name[0]))
        return fsc_is_num;
    
    int begin = 0;
    int end = MemoryCell_stogare->len;
    if (end == 0)
        return fsc_MemoryCell_is_not_found;
    
    while(true)
    {
        int ind = (begin + end) / 2;
        int c = strcmp((MemoryCell_stogare->list)[ind]->name, name);
        
        if (c == 0)
        {
            *res_MemoryCell = (MemoryCell_stogare->list)[ind];
            return fsc_ok;
        }
        else
        {
            if (begin == ind)
                return fsc_MemoryCell_is_not_found;
        }
        
        if (c < 0)
            begin = ind;
        else
            end = ind;
    }
}

int get_value(T_MemoryCell_storage* MemoryCell_storage, char const * input_value)
{
    T_MemoryCell* res_MemoryCell = NULL;
    enum status_codes res = get_MemoryCell(MemoryCell_storage, &res_MemoryCell, input_value);

    switch (res)
    {
        case fsc_ok:
            return res_MemoryCell->value;

        case fsc_is_num:
            return atoi(input_value);
            
        default:
            return 0;
    }
}

enum status_codes sum(T_MemoryCell_storage* MemoryCell_storage, int* res, char const *a, char const *b)
{
    *res = get_value(MemoryCell_storage, a) + get_value(MemoryCell_storage, b);
    return fsc_ok;
}

enum status_codes subtraction(T_MemoryCell_storage* MemoryCell_storage, int* res, char const *a, char const *b)
{
    *res = get_value(MemoryCell_storage, a) - get_value(MemoryCell_storage, b);
    return fsc_ok;
}

enum status_codes multiplication(T_MemoryCell_storage* MemoryCell_storage, int* res, char const *a, char const *b)
{
    
    *res = get_value(MemoryCell_storage, a) * get_value(MemoryCell_storage, b);
    return fsc_ok;
}

enum status_codes divide(T_MemoryCell_storage* MemoryCell_storage, int* res, char const *a, char const *b)
{
    int b_value = get_value(MemoryCell_storage, b);
    if (b_value == 0)
        return fsc_invalid_parameter;
    
    *res = get_value(MemoryCell_storage, a) / b_value;
    return fsc_ok;
}


enum status_codes mod(T_MemoryCell_storage* MemoryCell_storage, int* res, char const *a, char const *b)
{
    int b_value = get_value(MemoryCell_storage, b);
    if (b_value == 0)
        return fsc_invalid_parameter;
    
    *res = get_value(MemoryCell_storage, a) % b_value;
    return fsc_ok;
}

enum status_codes parse_line(T_MemoryCell_storage* MemoryCell_storage, char * line)
{
    enum status_codes res = fsc_ok;
    
    char* begin = line;
    char* end = line;
    
    int number_param = 0;
    
    char* param_0 = NULL;
    char* param_1 = NULL;
    char action = ';';
    char* param_2 = NULL;
    
    bool line_is_end = false;
    bool print_is_found = false;
    
    while((*end != 0) || (!line_is_end))
    {
        switch (number_param)
        {
            case 0:
                if (*end == ' ' || *end == '=' || *end == ';')
                {
                    line_is_end = (*end == ';');
                    *end = 0;
                    
                    if (strcmp(begin, "print") == 0)
                    {
                        print_is_found = true;
                    }
                    else
                    {
                        param_0 = begin;
                    }
                    
                    ++number_param;
                    begin = end + 1;
                }
                break;

            case 1:
            {
                char c = action = *end;
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == ';')
                {
                    line_is_end = (*end == ';');
                    *end = 0;
                    
                    param_1 = begin;
                    
                    ++number_param;
                    begin = end + 1;
                }
                break;
            }
            case 2:
            {
                char c = *end;
                if (c == ';')
                {
                    *end = 0;
                    line_is_end = true;
                    
                    param_2 = begin;
                }
                break;
            }
            default:
                break;
        }
        
        ++end;
    }
    
    if (print_is_found)
    {
        if (param_1 == NULL)
        {
            for (int i = 0; i < MemoryCell_storage->len; ++i)
                printf("%s=%d\n",(MemoryCell_storage->list)[i]->name, (MemoryCell_storage->list)[i]->value);
        }
        else
        {
            T_MemoryCell* res_MemoryCell = NULL;
            res = get_MemoryCell(MemoryCell_storage, &res_MemoryCell, param_1);
            
            if (res == fsc_ok)
            {
                printf("%s=%d\n", res_MemoryCell->name, res_MemoryCell->value);
                return fsc_ok;
            }
            else
            {
                printf("%s is not initialized\n", param_1);
                return fsc_invalid_parameter;
            }
        }
    }
    
    int res_value = 0;
    switch (action)
    {
        case '+':
            res = sum(MemoryCell_storage, &res_value, param_1, param_2);
            break;
        case '-':
            res = subtraction(MemoryCell_storage, &res_value, param_1, param_2);
            break;
        case '*':
            res = multiplication(MemoryCell_storage, &res_value, param_1, param_2);
            break;
        case '/':
            res = divide(MemoryCell_storage, &res_value, param_1, param_2);
            break;
        case '%':
            res = mod(MemoryCell_storage, &res_value, param_1, param_2);
            break;
        case ';':
        {
            res = fsc_ok;
            res_value = get_value(MemoryCell_storage, param_1);
            break;
        }
        default:
            res = fsc_invalid_parameter;
            break;
    }
    
    if (res != fsc_ok)
        return res;
    
    T_MemoryCell* res_MemoryCell = NULL;
    res = get_MemoryCell(MemoryCell_storage, &res_MemoryCell, param_0);
    
    if (res == fsc_invalid_parameter)
        return fsc_invalid_parameter;
    
    if (res == fsc_ok)
    {
        // Изменяем существующую переменную
        res_MemoryCell->value = res_value;
    }
    else
    {
        // Инициализируем новую
        res = add_data_to_storage(MemoryCell_storage, param_0, res_value);
        return res;
    }
    
    return fsc_ok;
}


enum status_codes scan_from_file(FILE* file_iput, T_MemoryCell_storage* MemoryCell_storage)
{
    enum status_codes res = fsc_ok;
    char* buffer = NULL;
    size_t size;
    while(!(feof(file_iput)))
    {
        getline(&buffer, &size, file_iput);
        res = parse_line(MemoryCell_storage, buffer);
        if (res != fsc_ok)
            break;
    }
    free(buffer);
    return res;
}

int main(int argc, const char * argv[])
{
    enum status_codes res = fsc_ok;
    
    if (argc < 2)
        res = fsc_invalid_parameter;
    
    FILE* file_input = fopen(argv[1], "r");
    if (file_input == NULL)
        res = fsc_file_is_not_found;
    
    T_MemoryCell_storage* storage = NULL;
    if (res == fsc_ok)
        res = create_MemoryCell_storage(&storage);
    
    if (res == fsc_ok)
        scan_from_file(file_input, storage);
    
    if (file_input != NULL)
        fclose(file_input);
    
    if (storage != NULL)
        clear_MemoryCell_storage(&storage);
    
    return 0;
}

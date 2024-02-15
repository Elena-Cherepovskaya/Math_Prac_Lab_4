//
//  T_data.h
//  5_list
//
//  Created by Лена on 24.01.2024.
//

#ifndef T_data_h
#define T_data_h

#include <stdbool.h>

typedef struct
{
    char operator;
    int operand;
    
    //Флажок на оператортор стоит
    bool is_operator;
} T_data;

#endif /* T_data_h */

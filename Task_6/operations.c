//
//  operations.c
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#include "operations.h"
#include "char_num_transformation.h"

#include <stdbool.h>

int get_operation_num(char operation_name)
{
    char* operation_list = "~?!+&|-<=";
    for (int i = 0; i < 9; ++i)
    {
        if (operation_name == operation_list[i])
            return i;
    }
    return 9;
}

int operands_number(char c)
{
    return (c == '~') ? 1 : 2;
}

char num_to_operation(int num)
{
    char* operation_list = "~?!+&|-<=";
    return operation_list[num];
}

int get_priority(int c)
{
    int res;
    switch (c)
    {
        case 0:
            res = 3;
            break;
        case 1:
            res = 2;
            break;
        case 2:
            res = 2;
            break;
        case 3:
            res = 2;
            break;
        case 4:
            res = 2;
            break;
        case 5:
            res = 1;
            break;
        case 6:
            res = 1;
            break;
        case 7:
            res = 1;
            break;
        case 8:
            res = 1;
            break;
        default:
            res = 0;
            break;
    }
    
    return res;
}

char cacalculate(char operator, char a, char b)
{
    int num_a = char_to_num(a);
    int num_b = char_to_num(b);
    
    switch (operator)
    {
        case '&':
            return num_to_char(num_a & num_b);
        case '|':
            return num_to_char(num_a | num_b);
        case '~':
            return num_to_char(!(num_a));
        //-> - оператор логической импликации
        case '-':
            return num_to_char(num_a <= num_b);
        case '+':
            return num_to_char((num_a == 1) && (num_b == 0));
        case '^':
            return num_to_char(num_a ^ num_b);
        case '=':
            return num_to_char(num_a == num_b);
        //! - оператор логического штриха Шеффера
        case '!':
            return num_to_char(!((num_a == 1) && (num_b == 1)));
        //? - оператор логической функции Вебба
        case '?':
            return num_to_char(((num_a == 0) && (num_b == 0)));
        default:
            break;
    }
    return 0;
}


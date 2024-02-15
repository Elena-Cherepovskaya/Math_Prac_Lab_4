//
//  operations.h
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#ifndef operations_h
#define operations_h

#include <stdbool.h>

int get_operation_num(char operation_name);
int operands_number(char c);
char num_to_operation(int num);
int get_priority(int c);
char cacalculate(char operator, char a, char b);
bool is_double_operation(char operstion);

#endif /* operations_h */

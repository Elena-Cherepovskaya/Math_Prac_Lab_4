//
//  main.c
//  5_list
//
//  Created by Лена on 14.12.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "stack.h"
#include "status_code.h"
#include "postfix_buffer.h"

bool is_operator(char* operators_list, char value)
{
    int i = 0;
    while(operators_list[i] != 0)
    {
        if (operators_list[i] == value)
            return true;
        ++i;
    }
    return false;
}

enum status_codes is_brackets_balance_correct(char* buffer)
{
    if (buffer == NULL)
        return fsc_invalid_parameter;
    
    int count = 0;
    char* p_buf = buffer;
    while(*p_buf != 0)
    {
        if (count < 0)
            return fsc_incorrect;
        
        if (*p_buf == '(')
            ++count;
        if (*p_buf == ')')
            --count;
        
        ++p_buf;
    }
    
    return (count == 0) ? fsc_ok : fsc_incorrect;
}

int operators_priority(int c)
{
    switch (c)
    {
        case '^':
            return 3;
        case '*':
            return 2;
        case '/':
            return 2;
        case '%':
            return 2;
        case '+':
            return 1;
        case '-':
            return 1;
    }
    return 0;
}

int char_to_num(char c)
{
    return (int)(c - '0');
}

int calculate(int a, int b, char operator)
{
    switch (operator)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '%':
            return a % b;
        case '^':
            return pow(a, b);
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    enum status_codes res = fsc_ok;
    
    if (argc < 2)
        res = fsc_invalid_parameter;
    
    FILE* file_input = NULL;
    char* operators_list = "+-*/%^(";
    char* buffer = NULL;
    if (res == fsc_ok)
    {
        for (int i = 1; i < argc; ++i)
        {
            file_input = fopen(argv[1], "r");
            if (file_input == NULL)
                res = fsc_file_is_not_found;
            else
                printf("\n%s\n", argv[i]);
            
            size_t size;
            T_postfix_buffer* postfix_buffer = NULL;
            if (res == fsc_ok)
                res = create_postfix_buffer(&postfix_buffer);
            
            if (res == fsc_ok)
            {
                int index = 0;
                while(!(feof(file_input)))
                {
                    getline(&buffer, &size, file_input);
                    res = is_brackets_balance_correct(buffer);
                    
                    int tmp_ind = (int)strlen(buffer);
                    if (buffer[tmp_ind - 1] == '\n')
                        buffer[tmp_ind - 1] = 0;
                    printf("\ninfix: %s\n", buffer);
                    
                    //Инфиксная в постфиксную
                    T_node* operators_stack = NULL;
                    int cur_num = 0;
                    bool num_is_ready = false;
                    char* p_buf = buffer;
                    
                    while(*p_buf != 0)
                    {
                        if ((*p_buf == '(') && (res == fsc_ok))
                        {
                            res = push(&operators_stack, is_operator(operators_list, *p_buf), *p_buf, operators_list);
                            ++p_buf;
                            continue;
                        }
                        
                        if ((*p_buf == ')') && (res == fsc_ok))
                        {
                            if (num_is_ready)
                            {
                                res = add_to_postfix_buffer(&postfix_buffer, is_operator(operators_list, cur_num), cur_num, operators_list);
                                cur_num = 0;
                                num_is_ready = false;
                            }
                            else
                                res = fsc_brackets_are_empty;
                            
                            if (res == fsc_ok)
                            {
                                while(true)
                                {
                                    T_node chek_node;
                                    
                                    res = pop(&operators_stack, &chek_node);
                                    if ((chek_node.data.operator == '(') || (res != fsc_ok))
                                        break;
                                    else
                                        res = add_to_postfix_buffer(&postfix_buffer, is_operator(operators_list, chek_node.data.operator), chek_node.data.operator, operators_list);
                                }
                            }
                            ++p_buf;
                            continue;
                        }
                        
                        if (is_operator(operators_list, *p_buf) && res == fsc_ok)
                        {
                            if (num_is_ready)
                            {
                                res = add_to_postfix_buffer(&postfix_buffer, is_operator(operators_list, cur_num), cur_num, operators_list);
                                cur_num = 0;
                                num_is_ready = false;
                            }
                            
                            if (res == fsc_ok)
                            {
                                while(true)
                                {
                                    if (is_stack_empty(operators_stack))
                                        break;
                                    
                                    T_node chek_node;
                                    res = pop(&operators_stack, &chek_node);
                                    
                                    if (res == fsc_ok)
                                    {
                                        if (operators_priority(chek_node.data.operator) >= operators_priority(*p_buf))
                                        {
                                            res = add_to_postfix_buffer(&postfix_buffer, is_operator(operators_list, chek_node.data.operator), chek_node.data.operator, operators_list);
                                            break;
                                        }
                                        else
                                        {
                                            res = push(&operators_stack, is_operator(operators_list, chek_node.data.operator), chek_node.data.operator, operators_list);
                                            break;
                                        }
                                    }
                                }
                                res = push(&operators_stack, is_operator(operators_list, *p_buf), *p_buf, operators_list);
                            }
                            ++p_buf;
                            continue;
                        }
                        
                        if (res == fsc_ok)
                        {
                            num_is_ready = true;
                            cur_num = cur_num * 10 + char_to_num(*p_buf);
                        }
                        ++p_buf;
                    }
                    
                    if (num_is_ready && res == fsc_ok)
                    {
                        res = add_to_postfix_buffer(&postfix_buffer, is_operator(operators_list, cur_num),  cur_num, operators_list);
                        cur_num = 0;
                        num_is_ready = false;
                    }
                    
                    while(!(is_stack_empty(operators_stack)) && res == fsc_ok)
                    {
                        T_node cur_node;
                        res = pop(&operators_stack, &cur_node);
                        
                        if (res == fsc_ok)
                            res = add_to_postfix_buffer(&postfix_buffer, is_operator(operators_list, cur_node.data.operator), cur_node.data.operator, operators_list);
                    }
                    
                    if (res == fsc_ok)
                    {
                        //Вывод постфиксной записи
                        printf("postfix: ");
                        for (int i = 0; i < postfix_buffer->len; ++i)
                        {
                            if (postfix_buffer->data[i].is_operator)
                                printf("%c", postfix_buffer->data[i].operator);
                            else
                                printf("%d", postfix_buffer->data[i].operand);
                        }
                        printf("\n");
                    }
                    
                    
                    //Вычисление польской записи
                    T_node* operands_stack = NULL;
                    if (res == fsc_ok)
                    {
                        for (int i = 0; i < postfix_buffer->len; ++i)
                        {
                            if (res == fsc_ok)
                            {
                                if (postfix_buffer->data[i].is_operator)
                                {
                                    T_node operand_a;
                                    T_node operand_b;
                                    
                                    res = (stack_len(operands_stack) < 2) ? fsc_not_enough_operands : fsc_ok;
                                    
                                    if (res == fsc_ok)
                                        res = pop(&operands_stack, &operand_b);
                                    
                                    if (res == fsc_ok)
                                        res = pop(&operands_stack, &operand_a);
                                    
                                    if (res == fsc_ok)
                                    {
                                        int calculation_res = calculate(operand_a.data.operand, operand_b.data.operand, postfix_buffer->data[i].operator);
                                        
                                        res = push(&operands_stack, is_operator(operators_list, calculation_res), calculation_res, operators_list);
                                    }
                                }
                                else
                                    res = push(&operands_stack, is_operator(operators_list, postfix_buffer->data[i].operand), postfix_buffer->data[i].operand, operators_list);
                            }
                            else
                                break;
                        }
                    }
                    
                    T_node calculations_res;
                    if (res == fsc_ok)
                        res = (stack_len(operands_stack) == 1) ? pop(&operands_stack, &calculations_res) : fsc_too_many_operands;
                    
                    if (res == fsc_ok)
                        printf("result: %d\n", calculations_res.data.operand);

                    if (operators_stack != NULL)
                        clear_stack(&operators_stack);
                    
                    if (res != fsc_ok)
                    {
                        int input_file_len = (int)strlen(argv[i]);
                        char* output_file_name = (char*)malloc(sizeof(char) * (strlen("_res") + input_file_len));
                        if (output_file_name == NULL)
                            res = fsc_memory_error_detected;
                        
                        int ind = 0;
                        for (int j = (input_file_len - 1); j >= 0; --j)
                        {
                            if (argv[i][j] == '.')
                                ind = j;
                        }
                        
                        strcpy(output_file_name, argv[i]);
                        strcpy(&(output_file_name[ind]), "_res");
                        strcat(output_file_name, &(argv[i][ind]));
                        
                        FILE* file_output = NULL;
                        if (res != fsc_memory_error_detected)
                            file_output = fopen(output_file_name, "w");
                        
                        if (file_output == NULL)
                            res = fsc_memory_error_detected;
                        
                        if (res != fsc_ok)
                        {
                            fprintf(file_output, "%s %d ", buffer, index);
                            switch (res)
                            {
                                case fsc_incorrect:
                                    fprintf(file_output, "Incorrect bracket balance\n");
                                    break;
                                case fsc_brackets_are_empty:
                                    fprintf(file_output, "Empty brackets detected\n");
                                    break;
                                case fsc_not_enough_operands:
                                    fprintf(file_output, "Not enough operands\n");
                                    break;
                                case fsc_too_many_operands:
                                    fprintf(file_output, "Too many operands\n");
                                    break;
                                default:
                                    break;
                            }
                        }
                        
                        if (output_file_name != NULL)
                        {
                            free(output_file_name);
                            output_file_name = NULL;
                        }
                        
                        if (file_output != NULL)
                            fclose(file_output);
                    }
                    
                    if (operands_stack != NULL)
                        clear_stack(&operands_stack);
                    clear_postfix_buffer(&postfix_buffer);
                    
                    ++index;
                }
            }
            
            if (file_input != NULL)
                fclose(file_input);
        }
    }
        
    return 0;
}

//(23+89)/56^1
//2389+561^/

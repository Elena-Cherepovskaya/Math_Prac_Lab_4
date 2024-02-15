//
//  transform_x_to_10.c
//  4
//
//  Created by Лена on 01.02.2024.
//

#include "transform_x_to_10.h"
#include "status_codes.h"

#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int char_to_num(char c)
{
    if (isalpha(c))
        return (isupper(c)) ? c - 55 : c - 87;
    return c - '0';
}

enum status_codes transform_x_to_10(int* res, char* num, int base)
{
    if (*res != 0 || num == NULL)
        return fsc_invalid_parameter;
    
    int len = (int)strlen(num);
    char* p_num = &(num[len - 1]);
    int cur_pow = 0;
    while(len != 0)
    {
        int tmp = char_to_num(*p_num);
        
        if (tmp >= base)
            return fsc_runtime_error;
        
        *res += (tmp * pow(base, cur_pow));
        --len;
        --p_num;
        ++cur_pow;
    }
    
    return fsc_ok;
}

double log_a_b(double a, double b)
{
    return (log(b) / log(a));
}

enum status_codes transform_10_to_x (char** res, int n, int base)
{
    if (*res != NULL)
        return fsc_invalid_parameter;
    
    if ((base < 2) || (base > 36))
        return fsc_runtime_error;
    
    if (n == 0)
    {
        *res = (char*)malloc(sizeof(char) * 2);
        if (*res == NULL)
            return fsc_memory_error_detected;
        (*res)[0] = '0';
        (*res)[1] = 0;
        return fsc_ok;
    }
    
    int len_of_n = floor(log_a_b(base, n)) + 1;
    
    if (*res != NULL)
        return fsc_invalid_parameter;
    
    *res = (char*)malloc(sizeof(char) * (len_of_n + 1));
    if (*res == NULL)
        return fsc_memory_error_detected;
    (*res)[len_of_n] = 0;
    
    while (n > 0)
    {
        len_of_n--;
        
        if (n % base >= 10)
            (*res)[len_of_n] = (n % base) - 10 + 'A';
        else
            (*res)[len_of_n] = (n % base) + '0';
        
        n /= base;
    }
    return fsc_ok;
}

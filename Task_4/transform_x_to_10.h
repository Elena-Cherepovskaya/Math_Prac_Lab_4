//
//  transform_x_to_10.h
//  4
//
//  Created by Лена on 01.02.2024.
//

#ifndef transform_x_to_10_h
#define transform_x_to_10_h

#include <stdio.h>

int char_to_num(char c);
enum status_codes transform_x_to_10(int* res, char* num, int base);
enum status_codes transform_10_to_x (char** res, int n, int base);

#endif /* transform_x_to_10_h */

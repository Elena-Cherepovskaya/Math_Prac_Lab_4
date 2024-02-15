//
//  file_generation.h
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#ifndef file_generation_h
#define file_generation_h

#include <stdbool.h>

bool is_leter(void);
enum status_codes generate_output_file(char** output_file, const char * input_file, int name_len);

#endif /* file_generation_h */

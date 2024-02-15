//
//  tree_calculation.h
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#ifndef tree_calculation_h
#define tree_calculation_h

#include "status_codes.h"
#include "tree.h"
#include "variables_count.h"

enum status_codes create_values_tree(T_node** new_current_node, T_node* current_node, T_list* list);
enum status_codes calculate_tree(T_node** current_node, T_list* list);

#endif /* tree_calculation_h */

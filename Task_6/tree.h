//
//  tree.h
//  4_6
//
//  Created by Лена on 01.02.2024.
//

#ifndef tree_h
#define tree_h

typedef struct
{
    char data;
    void* p_left;
    void* p_right;
}T_node;

enum status_codes create_node(T_node** res_node, char c);
void print_tree(T_node* current_node, int count);
void clear_tree(T_node** current_node);
enum status_codes type_of_node(T_node* node);

#endif /* tree_h */

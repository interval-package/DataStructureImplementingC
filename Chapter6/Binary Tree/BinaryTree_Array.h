//
// Created by Zza on 2022/4/12.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_ARRAY_H
#define DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_ARRAY_H

#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif


// Binary Tree using array

typedef struct Bin_Tree_Arr_Node{
    ELEMENT_TYPE data;
    int left, right, parent;
}bin_tree_arr_node, *p_arr_node;

typedef struct Binary_Tree_Array{
    p_arr_node elems;
    int len;
    int cur;
} Binary_Tree_Array, *Bin_Tree_Arr, *Bin_Tree_Arr_Node;

bool BinStaticTree_init(Bin_Tree_Arr tar, int total_size){
    tar->elems = (p_arr_node) malloc((int)sizeof(bin_tree_arr_node) * (total_size));
    tar->len = total_size;
    tar->cur = 0;
    tar->elems[0].right = tar->elems[0].left =tar->elems[0].parent = -1;
    return true;
}

bool BinStaticTree_destruct(Bin_Tree_Arr tar){
//    free((tar->elems));
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_ARRAY_H

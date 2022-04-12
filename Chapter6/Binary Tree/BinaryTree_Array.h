//
// Created by Zza on 2022/4/12.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_ARRAY_H
#define DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_ARRAY_H

#include <stdlib.h>
#include <errno.h>
#include <math.h>
#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

// Binary Tree using array

typedef struct Binary_Tree_Array{
    ELEMENT_TYPE *arr;
    int len;
} Binary_Tree_Array, *Bin_Tree_Arr, *Bin_Tree_Arr_Node;

Bin_Tree_Arr Init_BinArr();

#endif //DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_ARRAY_H

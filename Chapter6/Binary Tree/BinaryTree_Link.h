//
// Created by Zza on 2022/4/9.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_H
#define DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_H

// Binary Tree with linked node

#include <stdlib.h>
#include <errno.h>
#include <math.h>
#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

typedef struct Binary_Tree{
    ELEMENT_TYPE data;
// def left tree, right tree
    struct Binary_Tree *left, *right;
    struct Binary_Tree *parent;
} *Binary_Tree, TreeNode,*pTreeNode;

// 已知前序、中序遍历结果，还原二叉树

// 层序遍历



#endif //DATASTRUCTUREIMPLEMENTINGC_BINARYTREE_H

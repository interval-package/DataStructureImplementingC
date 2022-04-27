//
// Created by Zza on 2022/4/22.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_BINTREE_THREAD_H
#define DATASTRUCTUREIMPLEMENTINGC_BINTREE_THREAD_H

//Too many null pointers in current representation of binary trees
//n: number of nodes
//number of non-null links: n-1
//total links: 2n
//null links: 2n-(n-1)=n+1
//Replace these null pointers with some useful “threads”.


#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

typedef char ThreadTraverseType;

#define THREAD_INORDER 'i'
#define THREAD_PREORDER 'p'
#define THREAD_POSTORDER 'a'
#define THREAD_NOT 'n'

typedef char ThreadTag;

#define THREAD_TAG_LINK 'l'
#define THREAD_TAG_THREAD 'T'

typedef struct ThreadBinTreeNode{
    ELEMENT_TYPE data;
    struct ThreadBinTreeNode* left;
    struct ThreadBinTreeNode* right;
    union {
        struct {
            ThreadTag l_tag, r_tag;
        };
        ThreadTraverseType type;
    };
} ThreadBinTreeNode, *ThBiNode, *ThreadBinTree;

#include "BinaryTree_Link.h"
#include "./BinTreeTraverse/BinTreeTraverse.h"

bool _ThreadTree_Copy_BinTree(Binary_Tree tar, ThreadBinTree res){
    if(!tar){
        res = NULL;
        return true;
    } else{
        res = (ThBiNode) malloc(sizeof(ThreadBinTreeNode));
        res->data = tar->data;
        res->l_tag = THREAD_TAG_LINK;
        res->r_tag = THREAD_TAG_LINK;
        _ThreadTree_Copy_BinTree(tar->left,res->left);
        _ThreadTree_Copy_BinTree(tar->right,res->right);
    }
    return true;
}

// 两个指针，左指针-前线索，右指针后线索
// 设置一个头结点，头结点左指针指向root，右指针指向遍历结尾
// 两个dangling指针指向头结点

bool EnThreading_Inorder(){
    return false;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_BINTREE_THREAD_H

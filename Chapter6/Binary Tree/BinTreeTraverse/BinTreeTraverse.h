//
// Created by Zza on 2022/4/15.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_BINTREETRANSVERSE_H
#define DATASTRUCTUREIMPLEMENTINGC_BINTREETRANSVERSE_H

#include "../BinaryTree_Array.h"
#include "../BinaryTree_Link.h"
#include "../TreeUtils/BinTreeUtils.h"

#define BINARY_TREE_TRAVERSE_STACK

int PreOrderTraverse(pTreeNode root, void* action(), void* container);
int InOrderTraverse(pTreeNode root, void* action(), void* container);
int PostOrderTraverse(pTreeNode root, void* action(), void* container);

#ifdef BINARY_TREE_TRAVERSE_RECURSION
// using recursive method
void PreOrderTraverse(pTreeNode root, void* action()){
    if(NULL == root)
        return;
    action(root);
    PreOrderTraverse(root->left, action);
    PreOrderTraverse(root->right, action);
}

void MidOrderTraverse(pTreeNode root, void* action()){
    if(NULL == root)
        return;
    MidOrderTraverse(root->left, action);
    action(root);
    MidOrderTraverse(root->right, action);
}

void LastOrderTraverse(pTreeNode root, void* action()){
    if(NULL == root)
        return;
    LastOrderTraverse(root->left, action);
    LastOrderTraverse(root->right, action);
    action(root);
}
#endif

#ifdef BINARY_TREE_TRAVERSE_STACK
// using stack to imitate recursion

//int PreOrderTraverse(pTreeNode root, void* action(), void* container);
//int PostOrderTraverse(pTreeNode root, void* action(), void* container);
int InOrderTraverse(pTreeNode root, void* action(), void* container);

// in stack method 1
int InOrderTraverse(pTreeNode root, void* action(), void* container){
    _TStk stk;
    _tree_init_stk(stk);

#ifdef TREE_TRAVERSE_ACTION_1
//    使用栈模拟的中序，方法1
    while (stk->top){
        while(root){
            _tree_stk_push(stk, root);
            root = root->left;
        }
        _tree_stk_pop(stk, &root);
        action(root,container);
        root = root->right;
    }
#else
//    使用栈模拟的中序，方法2
    while(root || stk->top){
        if(root){
            _tree_stk_push(stk,root);
            root = root->left;
        }else{
            _tree_stk_pop(stk,&root);
            action(root,container);
            root = root->right;
        }
    }
#endif

    _tree_des_stk(stk);
    return 1;
}

#endif

#endif //DATASTRUCTUREIMPLEMENTINGC_BINTREETRANSVERSE_H

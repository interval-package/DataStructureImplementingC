//
// Created by Zza on 2022/4/15.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_BINTREETRANSVERSE_H
#define DATASTRUCTUREIMPLEMENTINGC_BINTREETRANSVERSE_H

#include "../BinaryTree_Array.h"
#include "../BinaryTree_Link.h"

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

int PreOrderTraverse(pTreeNode root, void* action(), void* container);
int InOrderTraverse(pTreeNode root, void* action(), void* container);
int PostOrderTraverse(pTreeNode root, void* action(), void* container);

#endif

#endif //DATASTRUCTUREIMPLEMENTINGC_BINTREETRANSVERSE_H

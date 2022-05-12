//
// Created by Zza on 2022/5/12.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H
#define DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H

#ifndef ELEM
#define ELEM
typedef char ELEMENT_TYPE;
#endif

#include "../../Binary Tree/BinaryTree_Link.h"
#include "../../Binary Tree/TreeUtils/BinTreeUtils.h"
#include <stdbool.h>
#include <stdio.h>

// 使用递归的方式
bool Generate_tree_pre(const char* info, Binary_Tree* head){
    if(*info == '#'){
        *head = NULL;
        info++;
        return true;
    } else{
        *head = malloc(sizeof(TreeNode));
        (*head)->data = *info;
        info++;
    }
    Generate_tree_pre(info, &(*head)->left);
    Generate_tree_pre(info, &(*head)->right);
    return true;
}

void Display_Node(pTreeNode tar){
    printf("%s",tar->data);
}

bool PreOrderTraverse(pTreeNode root, void* action(pTreeNode)){
    if(NULL == root)
        return true;
    action(root);
    PreOrderTraverse(root->left, action);
    PreOrderTraverse(root->right, action);
    return true;
}

bool MidOrderTraverse(pTreeNode root, void* action()){
    if(NULL == root)
        return true;
    MidOrderTraverse(root->left, action);
    action(root);
    MidOrderTraverse(root->right, action);
    return true;
}

bool LastOrderTraverse(pTreeNode root, void* action()){
    if(NULL == root)
        return true;
    LastOrderTraverse(root->left, action);
    LastOrderTraverse(root->right, action);
    action(root);
    return true;
}


void test_traverse(){
    Binary_Tree tree;
    Generate_tree_pre("ABC##DE#G##F###",&tree);
    printf("preorder: ");
    PreOrderTraverse(tree,Display_Node);
    printf("\ninorder: ");
    printf("\npostorder: ");
}


#endif //DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H

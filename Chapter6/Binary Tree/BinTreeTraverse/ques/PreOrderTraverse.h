//
// Created by Zza on 2022/4/12.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_PREORDERTRANSVERSE_H
#define DATASTRUCTUREIMPLEMENTINGC_PREORDERTRANSVERSE_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* preorderTraversal_(struct TreeNode* root, const int* returnSize){
    int *res = (int*)malloc(sizeof(int)*(*returnSize));
    int iter = 0;
    struct TreeNode* cur = root;
    while (iter<*returnSize){
        if(!cur){
            root = (root->right)?(root->right):(root->left);
            cur = root;
            continue;
        }
        res[iter] = cur->val;
        cur = cur->left;
        iter++;
    }
    return res;
}

// in recursive method

void preorder(struct TreeNode* root, int* res, int* resSize) {
    if (root == NULL) {
        return;
    }
    res[(*resSize)++] = root->val;
    preorder(root->left, res, resSize);
    preorder(root->right, res, resSize);
}

int* preorderTraversal__(struct TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 2000);
    *returnSize = 0;
    preorder(root, res, returnSize);
    return res;
}

// in iteration method

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* res = malloc(sizeof(int) * 2000);
    *returnSize = 0;
    if (root == NULL) {
        return res;
    }

    struct TreeNode *p1 = root, *p2 = NULL;

    while (p1 != NULL) {
        p2 = p1->left;
        if (p2 != NULL) {
            while (p2->right != NULL && p2->right != p1) {
                p2 = p2->right;
            }
            if (p2->right == NULL) {
                res[(*returnSize)++] = p1->val;
                p2->right = p1;
                p1 = p1->left;
                continue;
            } else {
                p2->right = NULL;
            }
        } else {
            res[(*returnSize)++] = p1->val;
        }
        p1 = p1->right;
    }
    return res;
}

// imitate main func

int PreOrder_Main(){
    struct TreeNode root, ch1, ch2, ch3;
    root.val = 0; ch1.val = 1; ch2.val = 2; ch3.val = 3;
    root.right = &ch1; ch1.left = &ch2; ch1.right = &ch3;
    root.left = ch2.right = ch2.left = ch3.right = ch3.left = NULL;
    int res = 4;
    int* tar = preorderTraversal(&root, &res);
    for(int i=0;i<res;i++)printf(" %d",tar[i]);
    free(tar);
    return 0;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_PREORDERTRANSVERSE_H

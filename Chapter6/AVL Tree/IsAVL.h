//
// Created by Zza on 2022/4/13.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_ISAVT_H
#define DATASTRUCTUREIMPLEMENTINGC_ISAVT_H
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int height(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    } else {
        return fmax(height(root->left), height(root->right)) + 1;
    }
}

bool isBalanced(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    } else {
        return fabs(height(root->left) - height(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
}

#endif //DATASTRUCTUREIMPLEMENTINGC_ISAVT_H

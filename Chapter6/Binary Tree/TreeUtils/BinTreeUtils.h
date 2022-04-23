//
// Created by Zza on 2022/4/17.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_TREEUTILS_H
#define DATASTRUCTUREIMPLEMENTINGC_TREEUTILS_H

#include "../BinaryTree_Array.h"
#include "../BinaryTree_Link.h"

// Tree Stack

#define _TREE_STACK_LEN 10

#ifndef TREE_STK
#define TREE_STK
typedef pTreeNode tNode;
#endif

typedef struct TreeStk{
    tNode* body;
    int top;
    int len;
} _TreeStk, *_TStk;

bool _tree_init_stk(_TStk tar){
    tar->body = (tNode*) malloc(sizeof(tNode)*_TREE_STACK_LEN);
    tar->top = 0;
    tar->len = _TREE_STACK_LEN;
    return tar->body;
}

bool _tree_des_stk(_TStk tar){
    free(tar->body);
    tar->body = NULL;
    tar->top = -1;
    tar->len = -1;
    return 1;
}

bool _tree_stk_push(_TStk tar, tNode obj){
    if(tar->top == tar->len){
        tar->len += _TREE_STACK_LEN;
        tar->body = (tNode*) realloc(tar->body,sizeof(tNode)*(tar->len));
    }
    tar->body[tar->top++] =  obj;
    return 1;
}

bool _tree_stk_pop(_TStk tar, tNode* container){
    if(tar->top){
        *container = tar->body[--(tar->top)];
        return 1;
    } else{
        return 0;
    }
}

// Tree Queue

typedef struct TreeQueue{

} _TreeQue, *_tQue;

bool _tree_init_que();

bool _tree_des_que();

bool _tree_enqueue();

bool _tree_dequeue();


#endif //DATASTRUCTUREIMPLEMENTINGC_TREEUTILS_H

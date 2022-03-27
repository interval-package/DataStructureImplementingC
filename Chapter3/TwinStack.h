//
// Created by Zza on 2022/3/27.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_TWINSTACK_H
#define DATASTRUCTUREIMPLEMENTINGC_TWINSTACK_H

#include <stdlib.h>
#include <errno.h>

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

typedef struct {
    int cap;
    int top_for, top_bac;
    ELEMENT_TYPE *stack;
} TwinStack, *tStack;

tStack TwinStack_Get(int TotalSize){
    tStack res = (tStack) malloc(sizeof(TwinStack));
    res->cap = TotalSize;
//    先种萝卜
    res->top_for = 0;
    res->top_bac = TotalSize-1;
    res->stack = (ELEMENT_TYPE*) malloc(sizeof(ELEMENT_TYPE)*TotalSize);
    return res;
}

void TwinStack_Destruct(tStack *obj){
    free((*obj)->stack);
    free(*obj);
    *obj = NULL;
}

// below declare the functions with param of stack selection,
// for 0 forward and 1 backward

void Push_tStack(tStack obj,ELEMENT_TYPE tar, int sel){
    if(obj->top_for>obj->top_bac){
        perror("full");
        return;
    }
    int pos = sel?obj->top_bac--:obj->top_for++;
    obj->stack[pos] = tar;
}

ELEMENT_TYPE Pop_tStack(tStack obj ,int sel){
    if(sel?!obj->top_for:obj->top_bac==obj->cap-1){
        perror("empty!");
        exit(0);
    }
    int pos = sel?++(obj->top_bac):--(obj->top_for);
    return obj->stack[pos];
}

#endif //DATASTRUCTUREIMPLEMENTINGC_TWINSTACK_H

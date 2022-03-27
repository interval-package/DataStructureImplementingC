//
// Created by Zza on 2022/3/27.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_QUEUEIMITATIONBYSTACK_H
#define DATASTRUCTUREIMPLEMENTINGC_QUEUEIMITATIONBYSTACK_H

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

#include "Stack.h"

typedef struct QueueOfStack{
    sta st_in;
    sta st_out;
} sQueue, *staQ;

staQ QueueOfStack_Create(int size){
    staQ res = (staQ)malloc(sizeof(sQueue));
    res->st_in = CreateStack(size);
    res->st_out = CreateStack(size);
    return res;
}

void QueueOfStack_Destruct(staQ *obj){
    free((*obj)->st_in);
    free((*obj)->st_out);
    free(*obj);
    *obj = NULL;
}

/*
 * 算法设计：一个带记忆的过程
 * 一个栈负责入，一个栈负责出
 * 入都入到入栈里面，出从出栈出来
 * 如果出栈为空，那么就把入栈的元素倾倒到出栈
 * */

int isEmpty_sQueue(staQ obj){
    return obj->st_in->top+obj->st_out->top;
}

int isFull_sQueue(staQ obj){
    return isFull(obj->st_in);
}

void sQueue_join(staQ obj, ELEMENT_TYPE tar){
    PushBack(obj->st_in, tar);
};

ELEMENT_TYPE sQueue_out(staQ obj){
    if(isEmpty(obj->st_out)){
        while(!isEmpty(obj->st_in)){
            PushBack(obj->st_out, Pop(obj->st_in));
        }
    }
    return Pop(obj->st_out);
}



#endif //DATASTRUCTUREIMPLEMENTINGC_QUEUEIMITATIONBYSTACK_H

//
// Created by Zza on 2022/3/18.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STACK_H
#define DATASTRUCTUREIMPLEMENTINGC_STACK_H
#include <stdlib.h>

//#define INIT_SIZE 100
#define INCREMENT 10

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

// =====================================================================================================================
// 使用数组实现的堆栈
typedef struct Stack_array {
    int len;
    int top;
    ELEMENT_TYPE* array;
} Stack_arr, *stk_arr;

Stack_arr* CreateStack(int size){
    stk_arr st = (stk_arr) malloc(sizeof(Stack_arr));
    st->len = size;
//    先挖坑，后种萝卜
    st->top = 0;
    st->array = (ELEMENT_TYPE*)malloc(sizeof(int)*size);
    return st;
}

void DestroyStack(stk_arr st){
    free(st->array);
    free(st);
}

int isFull(stk_arr st){return st->top == st->len;}

int isEmpty(stk_arr st){return !(st->top);}

void PushBack(stk_arr st, ELEMENT_TYPE obj){
    if(st->top == st->len){
        st->len += INCREMENT;
        st->array = (ELEMENT_TYPE*)realloc(st->array,st->len*sizeof(Stack_arr));
    }
    st->array[st->top++] = obj;
}

int PushBack_static(stk_arr st, ELEMENT_TYPE obj){
    if(st->top == st->len){
#ifdef EXIT_METHOD
        perror("full Stack");
//        设置的栈的长度是静态的，没有动态增加
        exit(1);
#else
        return 0;
#endif
    }
    st->array[st->top++] = obj;
    return 1;
};

ELEMENT_TYPE Pop(stk_arr st){
    if(st->top){
        return st->array[--(st->top)];
    } else{
        perror("empty");
        exit(1);
    }
}

// =====================================================================================================================

#include "../Chapter2/LinkedList.h"

// 什么叫代码重复利用
typedef lNode lStack_Node, *lStk;

// 这里只要使用之前定义好的函数就行了

#define lStackInit lListInitByLen
#define lStackDestroy lListDestroy
#define isEmpty_lStk isEmpty_byNext

void lStkPushBack(lStk obj, ELEMENT_TYPE tar){
    lListInsertRear(obj,tar);
    obj->len++;
}

ELEMENT_TYPE lStkPop(lStk obj){
    if(isEmpty_lStk(obj)){
        exit(42);
    }
    obj->len--;
    ELEMENT_TYPE res = obj->next->data;
    obj->next = obj->next->next;
    free(obj->next);
    return res;
}


#endif //DATASTRUCTUREIMPLEMENTINGC_STACK_H

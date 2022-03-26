//
// Created by Zza on 2022/3/18.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STACK_H
#define DATASTRUCTUREIMPLEMENTINGC_STACK_H
#include <stdlib.h>

//#ifndef ELEMENT_TYPE
//#define ELEMENT_TYPE int
//#endif

#define INIT_SIZE 100
#define INCREMENT 10

typedef int ELEMENT_TYPE;

// =====================================================================================================================
// 使用数组实现的堆栈
typedef struct Stack_array {
    int len;
    int top;
    ELEMENT_TYPE* array;
} Stack_arr, *sta;

Stack_arr* CreateStack(int size){
    sta st = (sta) malloc(sizeof(Stack_arr));
    st->len = size;
//    先挖坑，后种萝卜
    st->top = 0;
    st->array = (ELEMENT_TYPE*)malloc(sizeof(int)*size);
    return st;
}

void DestroyStack(sta st){
    free(st->array);
    free(st);
}

int isFull(sta st){return st->top == st->len;}

int isEmpty(sta st){return !(st->top);}

void PushBack(sta st, ELEMENT_TYPE obj){
    if(st->top == st->len){
        st->len += INCREMENT;
        st->array = (ELEMENT_TYPE*)realloc(st->array,st->len*sizeof(Stack_arr));
    }
    st->array[st->top++] = obj;
}

void PushBack_sta(sta st, ELEMENT_TYPE obj){
    if(st->top == st->len){
//        设置的栈的长度是静态的，没有动态增加
        perror("full Stack");
        exit(0);
    }
    st->array[st->top++] = obj;
};

ELEMENT_TYPE Pop(sta st){
    if(st->top){
        return st->array[--(st->top)];
    } else{
        perror("empty");
        exit(0);
    }
}

// =====================================================================================================================

#include "../Chapter2/LinkedList.h"

// 什么叫代码重复利用
typedef lNode lStack_N, *lStk;

// 这里只要使用之前定义好的函数就行了

linkedList lListInitByLen(int len);
void lListDestroy(linkedList *lk);
int isEmpty_byNext(linkedList l);

// 重新包装，对头节点使用就是入栈了
void lListInsertRear(lNode *p, ELEMENT_TYPE item);
void push_lStk(lStk p, ELEMENT_TYPE item){lListInsertRear(p,item);}


#endif //DATASTRUCTUREIMPLEMENTINGC_STACK_H

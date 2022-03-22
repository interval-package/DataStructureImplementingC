//
// Created by Zza on 2022/3/18.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STACK_H
#define DATASTRUCTUREIMPLEMENTINGC_STACK_H
#include <stdlib.h>
#define ELEMENT_TYPE int
#define INIT_SIZE 100
#define INCREMENT 10

// =====================================================================================================================
// 使用数组实现的堆栈
typedef struct Stack_array {
    int len;
    int top;
    ELEMENT_TYPE* array;
} Stack_arr, *sta;

Stack_arr* CreateStack(){
    sta st = (sta) malloc(sizeof(Stack_arr));
    st->len = INIT_SIZE;
//    先挖坑，后种萝卜
    st->top = 0;
    st->array = (ELEMENT_TYPE*)malloc(sizeof(int)*INIT_SIZE);
    return st;
}

void DestroyStack(sta st){
    free(st->array);
    free(st);
}

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

typedef struct Linked_Stack{
//    有点不想写了
} lStack, *lStk;

#endif //DATASTRUCTUREIMPLEMENTINGC_STACK_H

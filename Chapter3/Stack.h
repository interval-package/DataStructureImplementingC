//
// Created by Zza on 2022/3/18.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STACK_H
#define DATASTRUCTUREIMPLEMENTINGC_STACK_H
#include <stdlib.h>
#define ELEMENT_TYPE int
#define INIT_SIZE 100
#define INCREMENT 10

// 使用数组实现的堆栈
typedef struct Stack_array {
    int len;
    int top;
    ELEMENT_TYPE* array;
} Stack_arr;

Stack_arr InitStack(){
    Stack_arr st;
    st.len = INIT_SIZE;
//    先挖坑，后种萝卜
    st.top = 0;
    st.array = (ELEMENT_TYPE*)malloc(sizeof(int)*INIT_SIZE);
    return st;
}

void DestroyStack(Stack_arr *st){

}

void PushBack(Stack_arr* st){

};

#endif //DATASTRUCTUREIMPLEMENTINGC_STACK_H

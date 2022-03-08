//
// Created by 86189 on 2022/3/8.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_SEQUENTIAL_LIST_H
#define DATASTRUCTUREIMPLEMENTINGC_SEQUENTIAL_LIST_H
#include<stdio.h>
#include<errno.h>

#define INIT_LEN 100
#define INCREMENT 10
typedef int ELEMENT_TYPE
typedef struct {
    ELEMENT_TYPE *elementArray;
    int elementCount;
    int totalElemSize;
} SequentialList;

int SequentialListInit(SequentialList *La){
// 在初始化时使用n+1个元素，0号位存放哨兵元素
    tempPointer = (*ELEMENT_TYPE)malloc((INIT_LEN+1)*sizeof(ELEMENT_TYPE));
    if(tempPointer == NULL){
        perror("init memory malloc failed");
        La->elementArray = NULL;
        exit(EXIT_FAILURE);
        return 0;
    }
    La->elementArray = tempPointer;
    La->elementCount = 0;
    La->totalElemSize = INIT_LEN;
    return 1;
}

int SequentialListDestruct(SequentialList *La){
    if(!free(La->elementArray)){
        perror("free elementArray failed");
        return 0;
    }
    La->elementArray = NULL;
    La->elementCount = 0;
// 用总长-1来表示已经进行了释放
    La->totalElemSize = -1;
    return 1;
}

#define IS_FULL_SQLIST(p) (p)->elementCount==(p)->totalElemSize

int sqListIncrease(SequentialList *La, int times){
    ELEMENT_TYPE *tempPointer = (*ELEMENT_TYPE)realloc(La->elementArray,
                                         (La->totalElemSize+1+times*INCREMENT)*sizeof(ELEMENT_TYPE));
    if(tempPointer == NULL){
        perror("increase failed")
        return 0;
    }
    La->elementArray = tempPointer;
    La->totalElemSize += times*INCREMENT;
    return 1;
}

int sqListInsert(SequentialList *La,int pos,ELEMENT_TYPE tar){
    if(pos < 0 || pos > La->elementCount+1){
        perror("argument pos overflow");
        return -1;
    }
    if(IS_FULL_SQLIST(La->elementArray)){
        sqListIncrease(La,1);
    }
    int end = La->elementCount;
    while(end > pos){

    }
}

int compare_basic_int(ELEMENT_TYPE elem_1,ELEMENT_TYPE elem_2){
    return elem_1-elem_2;
}

// 使用低端哨兵方法查找
int LocateElem_LowEndSentry(SequentialList *La,ELEMENT_TYPE tar,int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE)){
// 获取末尾指针
    ELEMENT_TYPE *pArray = &(La->elementArray[La->elementCount]);
// 初始化哨兵0位
    La->elementArray[0] = tar;
    int i = La->elementCount;
    while(compare_int(tar,*pArray--))--i;
    return i;
}



#endif //DATASTRUCTUREIMPLEMENTINGC_SEQUENTIAL_LIST_H

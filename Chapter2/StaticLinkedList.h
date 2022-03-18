//
// Created by Zza on 2022/3/15.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STATICLINKEDLIST_H
#define DATASTRUCTUREIMPLEMENTINGC_STATICLINKEDLIST_H

#include <stdlib.h>
typedef int ELEMENT_TYPE;

typedef struct StaticListNode{
    union{
        int data;
        int spare_cursor;
    };
    int cursor;
} slNode;

typedef struct StaticList{
    int avail;
    int len;
    slNode *sList;
} sList;

sList sListCreate(int size){
    sList result;
    result.len = 0;
    result.avail = size;
//    多设置一位头结点
    result.sList = (slNode*)malloc(sizeof(slNode)*(size+1));
//    设置cursor为-1,表示还没有下一位
    result.sList[0].cursor=-1;
    result.sList[0].spare_cursor=size;
//    空闲链表的指针应当从尾部开始
    for(int i=1;i<=size;i++){
        result.sList[i].spare_cursor=i-1;
    }
    return result;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_STATICLINKEDLIST_H

//
// Created by Zza on 2022/3/15.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STATICLINKEDLIST_H
#define DATASTRUCTUREIMPLEMENTINGC_STATICLINKEDLIST_H

#include <stdlib.h>
#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

typedef struct StaticListNode{
    int len;
    int cursor;
} slNode;

typedef struct StaticList{
    int avail;
    int len;
    slNode *sList;
} sList;

sList sListCreate(int size){
    sList result;
    result.len = size;
    result.avail = 0;
    result.sList = (slNode*)malloc(sizeof(slNode)*(size+1));
    return result;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_STATICLINKEDLIST_H

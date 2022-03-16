//
// Created by Zza on 2022/3/16.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_DOUBLYLINKEDLIST_H
#define DATASTRUCTUREIMPLEMENTINGC_DOUBLYLINKEDLIST_H
#include <stdlib.h>
#include <errno.h>
typedef int ELEMENT_TYPE;

typedef struct DoublyLinkedListNode{
    struct DoublyLinkedListNode *prior, *rear;
    union {
        ELEMENT_TYPE data;
        int len;
    };
} DuNode, *DuList;

DuList DuListCreate(){
    DuList tar = (DuList)malloc(sizeof(DuNode));
    tar->len = 0;
    return tar;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_DOUBLYLINKEDLIST_H

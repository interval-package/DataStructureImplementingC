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
    tar->prior = NULL;
    tar->rear = NULL;
    return tar;
}

void DuListDestruct(DuList l){
    DuList temp;
    while(l){
        temp = l->rear;
        free(l);
        l = temp;
    }
}

void DuListFirstDelete(DuList l){
    DuList temp = l->rear;
    if(!temp)return;
    l->rear = temp->rear;
    temp->rear->prior = l;
    free(temp);
}

void DuListFirstXDelete(DuList l, ELEMENT_TYPE tar){
    do{
        l = l->rear;
    } while (l && l->data != tar);
    if(l){
        l->prior->rear = l->rear;
        if(l->rear)l->rear->prior = l->prior;
        free(l);
    }
}

#endif //DATASTRUCTUREIMPLEMENTINGC_DOUBLYLINKEDLIST_H

//
// Created by 86189 on 2022/3/12.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H
#define DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H
#include <stdlib.h>
#include <errno.h>
typedef int elementType;
typedef struct lNode{
    elementType data;
    struct elementType* next;
} lNode, *linkedList;

__attribute__((unused)) linkedList lListInit(){
    lNode *p = (lNode*)malloc(sizeof(lNode));
    if(!p)abort(1);
    p->next = NULL;
    p->data = 0;
    return p;
}

__attribute__((unused)) void lListDestroyRegress(linkedList l) {
    if(l == NULL){
        return;
    }else{

    }
}


#endif //DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H

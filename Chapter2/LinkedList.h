//
// Created by 86189 on 2022/3/12.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H
#define DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H

#include <errno.h>
typedef int ELEMENT_TYPE;
typedef struct lNode{
    ELEMENT_TYPE data;
    struct lNode* next;
} lNode, *linkedList;

linkedList lListInit(){
    lNode *p = (lNode*)malloc(sizeof(lNode));
    if(!p)abort(1);
    p->next = NULL;
    p->data = 0;
    return p;
}

linkedList lListInitByLen(int len){
    lNode *p = (lNode*)malloc(sizeof(lNode));
    if(!p)abort(1);
    p->data = len;
    lNode *r = p;
    int i = 1;
    while(i<=len){
        r->next = (lNode*)malloc(sizeof(lNode));
        r = r->next;
    }
    r->next = NULL;
    return p;
}

void lListDestroyRegress(linkedList l) {
    if(l == NULL){
        return;
    }else{
        lListDestroyRegress(l->next);
        free(l);
    }
}

void lListInsertRear(lNode *p, ELEMENT_TYPE item){
    lNode *r = (lNode*)malloc(sizeof(lNode));
    r->next = p->next;
    r->data = item;
    p->next = r;
}

void lListInsertPrior(lNode *p, ELEMENT_TYPE item){
    lNode *r = (lNode*)malloc(sizeof(lNode));
    r->next = p->next;
    p->next = r;
    r->data = p->data;
    p->data = item;
}

void lListInsertById(linkedList p, int pos,ELEMENT_TYPE item){
    if(pos>p->data){
        perror("exceed boundary");

        abort(1);
    }
    for(int i=1;i<=pos;i++){
        p = p->next;
    }
    lListInsertRear(p, item);
}

void deleteRearByNode(lNode *p){
    if(!p->next)return;
    lNode *r = (p->next)->next;
    free(p->next);
}


#endif //DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H

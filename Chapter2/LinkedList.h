//
// Created by 86189 on 2022/3/12.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H
#define DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H

#include <stdlib.h>
#include <errno.h>
#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif
typedef struct lNode{
    union {
        ELEMENT_TYPE data;
        int len;
    };
    struct lNode* next;
} lNode, *linkedList;

//========================================================================

linkedList lListInit();

linkedList lListInitByLen(int len);

void lListDestroy(linkedList *lk);

int isEmpty_byLen(linkedList l);

int isEmpty_byNext(linkedList l);

int updateLen(linkedList l);

ELEMENT_TYPE lListFindElem(linkedList l,int pos);

// it would delete the elem found in list
ELEMENT_TYPE lListGetElem(linkedList l,int pos);

void ChangeElem(linkedList l,int pos, ELEMENT_TYPE tar);

void lListInsertRear(lNode *p, ELEMENT_TYPE item);

void lListInsertPrior(lNode *p, ELEMENT_TYPE item);

void lListInsertById(linkedList p, int pos,ELEMENT_TYPE item);

// It's a dangerous action without len change
void deleteRearByNode(lNode *p);

// Delete the node in the pos
void deleteById(linkedList p,int pos);

void Reverse_lList(linkedList p0);

//========================================================================

linkedList lListInit(){
    lNode *p = (lNode*)malloc(sizeof(lNode));
    if(!p)abort();
    p->next = NULL;
    p->len = 0;
    return p;
}

linkedList lListInitByLen(int len){
    lNode *p = (lNode*)malloc(sizeof(lNode));
    if(!p)abort();
    p->len = len;
    lNode *r = p;
    int i = 1;
    while(i<=len){
        r->next = (lNode*)malloc(sizeof(lNode));
        r = r->next;
        i++;
    }
    r->next = NULL;
    return p;
}

// destroy func should be cautious about the wild pointer
//void lListDestroyRegress(linkedList l) {
//    if(l == NULL){
//        return;
//    }else{
//        lListDestroyRegress(l->next);
//        free(l);
//    }
//}

void lListDestroy(linkedList *lk){
    lNode *temp = NULL, *l=*lk;
    while(l){
        temp = l->next;
        free(l);
        l = temp;
    }
    *lk = NULL;
}

int isEmpty_byLen(linkedList l){
    return l->len==0;
}

int isEmpty_byNext(linkedList l){
    return l->next != NULL;
}

int updateLen(linkedList l){
    int i = 0;
    linkedList temp = l;
    while(l->next){
        i++;
        l = l->next;
    }
    temp->len = i;
    return i;
}

ELEMENT_TYPE lListFindElem(linkedList l,int pos){
    if(pos>l->len)abort();
    int i=1;
    while(i<pos){
        l=l->next;
        i++;
    }
    return l->next->data;
}

ELEMENT_TYPE lListGetElem(linkedList l,int pos){
    if(pos>l->len)abort();
    int i=1;
    ELEMENT_TYPE res;
    while(i<pos){
        l=l->next;
        i++;
    }
    res = l->next->data;
    deleteRearByNode(l);
    return res;
}

void ChangeElem(linkedList l,int pos, ELEMENT_TYPE tar){
    if(pos>l->len)abort();
    int i=1;
    while(i<pos){
        l=l->next;
        i++;
    }
    l->next->data = tar;
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
    if(pos>p->len){
        perror("exceed boundary");
        abort();
    }
    p->len++;
    for(int i=1;i<=pos;i++){
        p = p->next;
    }
    lListInsertRear(p, item);
}

// It's a dangerous action without len change
void deleteRearByNode(lNode *p){
    if(!p->next)return;
    lNode *r = (p->next)->next;
    free(p->next);
    p->next = r;
}

// Delete the node in the pos
void deleteById(linkedList p,int pos){
    if(pos<=0||pos>p->len){
        perror("exceed bound");
        return;
    }
    p->len--;
    int i=1;
    while(i<pos){
        p=p->next;
        i++;
    }
    deleteRearByNode(p);
}

void Reverse_lList(linkedList p0){
//    我们认为是有头结点的，p0为头节点指针

//    设置新的头节点
    lNode *temp, newHead;
    newHead.next = NULL;

    while (p0->next){
//        从原来的链表上摘下结点
        temp = p0->next;
        p0->next = temp->next;
//  把摘下结点头插到新的链表上
        temp->next = newHead.next;
        newHead.next = temp;
    }
    p0->next = newHead.next;
}

void Insert_X_Linked(linkedList p0,ELEMENT_TYPE tar){
    linkedList temp;
    do{
        temp = p0;
        p0 = p0->next;
    }while(p0 && p0->data<tar);
    lListInsertRear(temp,tar);
};

#include <stdio.h>

void DispLinkedList(linkedList obj){
    printf("\n");
    while(obj->next){
        obj = obj->next;
        printf("%d\t",obj->data);
    }
    printf("\n");
}

#ifndef MAIN_FUNC
#define MAIN_FUNC
void LinkedListMain(){
    int len = 10;
    linkedList ls = lListInitByLen(len);
//    演示修改函数
    printf("yet not update:");
    DispLinkedList(ls);
    for(int i=0;i<len;i++){
        ChangeElem(ls,i+1,i+1);
    }
    printf("updated:");
    DispLinkedList(ls);


    Insert_X_Linked(ls,7);
    Insert_X_Linked(ls,5);
    printf("insert:");
    DispLinkedList(ls);

    printf("reversed:");
    Reverse_lList(ls);
    DispLinkedList(ls);
    
    printf("deleted");
    deleteById(ls,6);
    DispLinkedList(ls);
}
#endif

#endif //DATASTRUCTUREIMPLEMENTINGC_LINKEDLIST_H

//
// Created by Zza on 2022/3/18.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_CRICULAR_LINKED_LIST_H
#define DATASTRUCTUREIMPLEMENTINGC_CRICULAR_LINKED_LIST_H
#include <stdlib.h>
typedef int ELEMENT_TYPE;

typedef struct Circular_LNode{
    union {
        ELEMENT_TYPE data;
        int len;
    };
    struct Circular_LNode *next;
}clNode, *clList;

// 初始化
clList Circular_List_Create(){
    clList headNode = (clList)malloc(sizeof(clNode));
    headNode->next = headNode;
    headNode->len = 0;
    return headNode;
}

clList clListInit(int len){
//    设置头结点
    clList temp, head, p = (clList)malloc(sizeof(clNode));
    head = p;
    for(int i=0; i<len; i++){
        temp = (clList)malloc(sizeof(clNode));
        p->next = temp;
        p = temp;
    }
    temp->next = head;
//    返回的是尾结点
    return temp;
}

void Destroy_clList(clList cll){
    clList temp = cll->next;
    cll->next=NULL;
    cll = temp;
    while(cll->next){
        temp = cll->next;
        free(cll);
        cll = temp;
    }
}

// 循环链表都是用尾指针来表示链表
void clList_RearInsert(clList *cll, ELEMENT_TYPE data){
    clList temp = (clList)malloc(sizeof(clNode));
    temp->data = data;
    temp->next = (*cll)->next;
    (*cll)->next = temp;
    temp->next->len++;
    cll = &temp;
}

//
ELEMENT_TYPE clList_Pop(clList cll){
    if(cll->next == cll){
        abort();
    }
    ELEMENT_TYPE res;
    clNode *p = cll->next;
    res = p->data;
    cll->next = p->next;
    free(p);
    cll->len--;
    return res;
}

void right_Delete(clList *cll){
    if((*cll)->next == *cll){
        return;
    }
    clList temp = *cll;
    while(temp->next!=(*cll)){
        temp = temp->next;
    }
    temp->next = (*cll)->next;
    free(*cll);
    *cll = temp;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_CRICULAR_LINKED_LIST_H

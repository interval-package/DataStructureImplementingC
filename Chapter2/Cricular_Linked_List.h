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
    clList rearNode = (clList)malloc(sizeof(clNode));
    rearNode->next = rearNode;
    rearNode->len = 0;
    return rearNode;
}

void Destroy_clList(clList cll){

}

void clList_HeadInsert(clList cll, ELEMENT_TYPE data){
    clList temp = (clList)malloc(sizeof(clNode));
    temp->data = data;
    temp->next = cll->next;
    cll->next = temp;
    cll->len++;
}

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

#endif //DATASTRUCTUREIMPLEMENTINGC_CRICULAR_LINKED_LIST_H

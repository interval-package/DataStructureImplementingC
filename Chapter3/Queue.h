//
// Created by Zza on 2022/3/25.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_QUEUE_H
#define DATASTRUCTUREIMPLEMENTINGC_QUEUE_H

#include "../Chapter2/Circular_Linked_List.h"

// 实际上这一部分代码是已经写过了，copy过来吧
typedef clNode QueueNode, *Queue;

#define QueueCreate Circular_List_Create
#define QueueCreateByLen(len) clListInit(len)
#define QueueDestroy Destroy_clList

// 在之前我们已经实现了，用尾指针来表示循环列表
// 表头表示

void QueueJoin(Queue *que, ELEMENT_TYPE tar){
    Queue p = malloc(sizeof(QueueNode));
    p->data = tar;
    p->next = (*que)->next;
    (*que)->next = p;
    p->next->len++;
    *que = p;
}

ELEMENT_TYPE OutQueue(Queue *que){
    Queue temp, head = (*que)->next;
    temp = head->next;
    if(!head->len){
        exit(1);
    }
    head->len--;

    ELEMENT_TYPE res = head->next->data;
    head->next = head->next->next;
    free(temp);
    if(!head->len){
//    要考虑只有最后一个元素的情况
        *que = head;
    }
    return res;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_QUEUE_H

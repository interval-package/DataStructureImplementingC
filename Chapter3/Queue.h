//
// Created by Zza on 2022/3/25.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_QUEUE_H
#define DATASTRUCTUREIMPLEMENTINGC_QUEUE_H

#include "../Chapter2/Circular_Linked_List.h"

// 实际上这一部分代码是已经写过了，copy过来吧
typedef clNode QueueNode, *Queue;

#define QueueCreate Circular_List_Create
#define QueueCreateByLen clListInit
#define QueueDestroy Destroy_clList

#define isEmpty_Que isEmpty_clList

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

// 使用顺序表实现循环队列

// (rear - front + m) % m

#define QUE_LEN 100

typedef struct sqQueue{
    int rear, front;
    ELEMENT_TYPE *array;
    int len;
} sqQueue, *psqQue;

sqQueue sqQueue_Create(int len){
    sqQueue res;
    res.len = len;
    res.rear = res.front = 0;
    res.array = (ELEMENT_TYPE*) malloc(sizeof(ELEMENT_TYPE)*len);
    return res;
}

/*
 * rear point the next place without elem
 * front point the place have elem
 *
 * when the front - rear == 1 (using a blank place), it should be full.
 * */

int isFull_sqQue(const psqQue sq){
//    return (sq->front - sq->rear + sq->len) % sq->len == 1;
    return (sq->rear + 1) % sq->len == sq->front;
}

int isEmpty_sqQue(const psqQue sq){
    return sq->rear ==  sq->front;
}

void sqQueue_In(psqQue sq, ELEMENT_TYPE tar){
    if(isFull_sqQue(sq))return;
    sq->array[sq->rear] = tar;
    sq->rear = (sq->rear+1) % sq->len;
};

ELEMENT_TYPE sqQueue_Out(psqQue sq){
    if(isEmpty_sqQue(sq)){
        exit(-1);
    }
    ELEMENT_TYPE res = sq->array[sq->front];
    sq->front = (sq->front+1)%sq->len;
    return res;
};

int sqQueue_getLen(psqQue sq){
//    但凡出现差值操作，都一定是要加上长度然后取模
    return (sq->rear - sq->front + sq->len) % sq->len;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_QUEUE_H

# Stack And Queue

## 一、需求分析

在本次设计中的设计与实现的接口，会在接下来的实验中重复使用。

## 二、ADT设计

## 三、使用说明

### 1.基本结构

#### 顺序结构stack

```c
// 使用数组实现的堆栈
typedef struct Stack_array {
    int len;
    int top;
    ELEMENT_TYPE* array;
} Stack_arr, *stk_arr;
```



#### 链式结构stack

```c
typedef struct lNode{
    union {
        ELEMENT_TYPE data;
        int len;
    };
    struct lNode* next;
} lNode, *linkedList;

// 代码复用
typedef lNode lStack_Node, *lStk;
```



#### 顺序结构queue

```c
typedef struct sqQueue{
    int rear, front;
    ELEMENT_TYPE *array;
    int len;
} sqQueue, *psqQue;
```



#### 链式结构queue

```c
typedef struct lNode{
    union {
        ELEMENT_TYPE data;
        int len;
    };
    struct lNode* next;
} lNode, *linkedList;

typedef clNode QueueNode, *Queue;
```



### 2.API接口

#### 顺序结构stack

##### create and destruct

`CreateStack`

```c
Stack_arr* CreateStack(int size)
```

| param    | type | description |
| -------- | ---- | ----------- |
| int size | int  | 初始化容量  |

`DestroyStack`

```c
void DestroyStack(stk_arr st)
```

| param     | type  | description                  |
| --------- | ----- | ---------------------------- |
| `stk_arr` | ` st` | 由之前构造函数创建的动态对象 |

##### full or empty

```c
int isFull(stk_arr st){return st->top == st->len;}

int isEmpty(stk_arr st){return !(st->top);}
```

##### Pushback

`PushBack`

`PushBack_static`

```c
void PushBack(stk_arr st, ELEMENT_TYPE obj);
动态装入，当对满栈装入时，会使得增加长度

void PushBack_static(stk_arr st, ELEMENT_TYPE obj);
静态装入，满则溢出
```

| param | type         | description |
| ----- | ------------ | ----------- |
| st    | stk_arr      | 目标栈      |
| obj   | ELEMENT_TYPE | 数据        |

##### Pop

`Pop`

```c
ELEMENT_TYPE Pop(stk_arr st)
```

#### 链式结构stack

```c
#define lStackInit lListInitByLen
#define lStackDestroy lListDestroy
#define isEmpty_lStk isEmpty_byNext
```

##### `lStkPushBack`

##### `lStkPop`

#### 顺序结构queue

#### 链式结构queue

### 3.注意事项

## 四、调试结果

## 五、运行结果

## 六、源代码

### stack

```c
//
// Created by Zza on 2022/3/18.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STACK_H
#define DATASTRUCTUREIMPLEMENTINGC_STACK_H
#include <stdlib.h>

//#define INIT_SIZE 100
#define INCREMENT 10

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

// =====================================================================================================================
// 使用数组实现的堆栈
typedef struct Stack_array {
    int len;
    int top;
    ELEMENT_TYPE* array;
} Stack_arr, *stk_arr;

Stack_arr* CreateStack(int size){
    stk_arr st = (stk_arr) malloc(sizeof(Stack_arr));
    st->len = size;
//    先挖坑，后种萝卜
    st->top = 0;
    st->array = (ELEMENT_TYPE*)malloc(sizeof(int)*size);
    return st;
}

void DestroyStack(stk_arr st){
    free(st->array);
    free(st);
}

int isFull(stk_arr st){return st->top == st->len;}

int isEmpty(stk_arr st){return !(st->top);}

void PushBack(stk_arr st, ELEMENT_TYPE obj){
    if(st->top == st->len){
        st->len += INCREMENT;
        st->array = (ELEMENT_TYPE*)realloc(st->array,st->len*sizeof(Stack_arr));
    }
    st->array[st->top++] = obj;
}

void PushBack_static(stk_arr st, ELEMENT_TYPE obj){
    if(st->top == st->len){
//        设置的栈的长度是静态的，没有动态增加
        perror("full Stack");
        exit(0);
    }
    st->array[st->top++] = obj;
};

ELEMENT_TYPE Pop(stk_arr st){
    if(st->top){
        return st->array[--(st->top)];
    } else{
        perror("empty");
        exit(0);
    }
}

// =====================================================================================================================

#include "../Chapter2/LinkedList.h"

// 什么叫代码重复利用
typedef lNode lStack_Node, *lStk;

// 这里只要使用之前定义好的函数就行了

#define lStackInit lListInitByLen
#define lStackDestroy lListDestroy
#define isEmpty_lStk isEmpty_byNext

void lStkPushBack(lStk obj, ELEMENT_TYPE tar){
    lListInsertRear(obj,tar);
    obj->len++;
}

ELEMENT_TYPE lStkPop(lStk obj){
    if(isEmpty_lStk(obj)){
        exit(42);
    }
    obj->len--;
    ELEMENT_TYPE res = obj->next->data;
    obj->next = obj->next->next;
    free(obj->next);
    return res;
}


#endif //DATASTRUCTUREIMPLEMENTINGC_STACK_H
```

### queue

```c
//
// Created by Zza on 2022/3/25.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_QUEUE_H
#define DATASTRUCTUREIMPLEMENTINGC_QUEUE_H

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

#include "../Chapter2/Circular_Linked_List.h"

// 实际上这一部分代码是已经写过了，copy过来吧
// 在之前我们已经实现了，用尾指针来表示循环列表
// 表头表示
typedef clNode QueueNode, *Queue;

#define QueueCreate Circular_List_Create
#define QueueDestroy Destroy_clList
#define isEmpty_Que isEmpty_clList

int QueueLen(Queue que){
    return que->next->len;
}

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


//-----------------------------------------------------------------------------

// 使用顺序表实现循环队列

// (rear - front + m) % m
/*
 * rear point the next place without elem
 * front point the place have elem
 * when the front - rear == 1 (using a blank place), it should be full.
 * */

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

int isFull_sqQue(psqQue sq){
//    return (sq->front - sq->rear + sq->len) % sq->len == 1;
    return (sq->rear + 1) % sq->len == sq->front;
}

int isEmpty_sqQue(psqQue sq){
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
```

## 七、总结


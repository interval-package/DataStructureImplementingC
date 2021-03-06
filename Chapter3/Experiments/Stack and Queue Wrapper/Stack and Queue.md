# Stack And Queue

## 一、需求分析

在本次设计中的设计与实现的接口，会在接下来的实验中重复使用。

（⼀）任务
1. 建⽴⼀个顺序栈
2. 建⽴⼀个循环顺序队列
3. 分别实现栈和队列的基本操作

（⼆）规定

1. 输⼊的形式和输⼊值的范围：程序是按数字键选择对应功能的，在各项功能中，创建、插⼊、删除、查找需要输⼊数据，输⼊的数据应为ASCII字符。
2. 输出的形式：在初始化后显示初始化成功，在插⼊删除数据后会打印插/删成功，在遍历后会显示所有的元素，在查找后会显示指定的元素。
3. 程序1（顺序栈）所能达到的功能：初始化；⼊栈；出栈；得到栈顶元素；遍历；判空
4. 程序2（循环队列）所能达到的功能：初始化；创建队列；⼊队；出队；得到队⾸元素；得到⻓
  度；判空；遍历

## 二、ADT设计

详细见下接口设计。

## 三、使用说明

### 1.基本结构

#### 顺序结构stack

```c
// 使用数组实现的堆栈
typedef struct Stack_array {
    int len;
    int top;
    ELEMENT_TYPE* array;
} Stack_arr, *stk;
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
void DestroyStack(stk st)
```

| param     | type  | description                  |
| --------- | ----- | ---------------------------- |
| `stk` | ` st` | 由之前构造函数创建的动态对象 |

##### full or empty

```c
int isFull(stk st){return st->top == st->len;}

int isEmpty(stk st){return !(st->top);}
```

##### Pushback

`PushBack`

`PushBack_static`

```c
void PushBack(stk st, ELEMENT_TYPE obj);
动态装入，当对满栈装入时，会使得增加长度

void PushBack_static(stk st, ELEMENT_TYPE obj);
静态装入，满则溢出
```

| param | type         | description |
| ----- | ------------ | ----------- |
| st    | stk      | 目标栈      |
| obj   | ELEMENT_TYPE | 数据        |

##### Pop

`Pop`

```c
ELEMENT_TYPE Pop(stk st)
```

| param     | type         | description                                  |
| --------- | ------------ | -------------------------------------------- |
| `stk` | ` st`        | 目标栈                                       |
| return    | ELEMENT_TYPE | 存储的值                                     |
| errno     | 1            | 当对空栈进行出栈操作的时候，使得程序跳出运行 |

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

对于pushback操作，需要用宏来定义其异常处理操作，当我们使用静态操作时，默认使用的是，返回0。但是我们可以通过设置宏来使得该操作不会返回值，而是退出程序。

## 四、调试结果

操作稳定性好，调试时，未发生异常错误。

## 五、运行结果

在这里，我们不进行运行测试了。

直接在后面对于接口调用的时候，测试接口的稳定性。

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
} Stack_arr, *stk;

Stack_arr* CreateStack(int size){
    stk st = (stk) malloc(sizeof(Stack_arr));
    st->len = size;
//    先挖坑，后种萝卜
    st->top = 0;
    st->array = (ELEMENT_TYPE*)malloc(sizeof(int)*size);
    return st;
}

void DestroyStack(stk st){
    free(st->array);
    free(st);
}

int isFull(stk st){return st->top == st->len;}

int isEmpty(stk st){return !(st->top);}

void PushBack(stk st, ELEMENT_TYPE obj){
    if(st->top == st->len){
        st->len += INCREMENT;
        st->array = (ELEMENT_TYPE*)realloc(st->array,st->len*sizeof(Stack_arr));
    }
    st->array[st->top++] = obj;
}

void PushBack_static(stk st, ELEMENT_TYPE obj){
    if(st->top == st->len){
//        设置的栈的长度是静态的，没有动态增加
        perror("full Stack");
        exit(0);
    }
    st->array[st->top++] = obj;
};

ELEMENT_TYPE Pop(stk st){
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

void EnQueue(Queue *que, ELEMENT_TYPE tar){
    Queue p = malloc(sizeof(QueueNode));
    p->data = tar;
    p->next = (*que)->next;
    (*que)->next = p;
    p->next->len++;
    *que = p;
}

ELEMENT_TYPE DeQueue(Queue *que){
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

void EnQueue_Sq(psqQue sq, ELEMENT_TYPE tar){
    if(isFull_sqQue(sq))return;
    sq->array[sq->rear] = tar;
    sq->rear = (sq->rear+1) % sq->len;
};

ELEMENT_TYPE DeQueue_Sq(psqQue sq){
    if(isEmpty_sqQue(sq)){
        exit(-1);
    }
    ELEMENT_TYPE res = sq->array[sq->front];
    sq->front = (sq->front+1)%sq->len;
    return res;
};

int getLen_sqQue(psqQue sq){
//    但凡出现差值操作，都一定是要加上长度然后取模
    return (sq->rear - sq->front + sq->len) % sq->len;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_QUEUE_H
```

## 七、总结


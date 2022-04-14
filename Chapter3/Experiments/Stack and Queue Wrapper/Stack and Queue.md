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

##### full or empty

##### Pushback

`PushBack`

`PushBack_static`

##### Pop

`Pop`

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

## 七、总结


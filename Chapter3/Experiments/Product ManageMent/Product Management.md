# Product Management

## 一、需求分析



## 二、ADT设计

```c
typedef int product, *prod;

typedef int time;

#ifndef ELEM
typedef product ELEMENT_TYPE;
#define ELEM
#endif

#include "../../Stack.h"

typedef stk_arr Cupboard;
```

## 三、使用说明

### 1.基本结构

我们对于货物的标识只有生产日期一个，所以我们选用了int作为我们货物的类型。

```c
#ifndef MAIN_FUNC
#define MAIN_FUNC
void test_main();
#endif

typedef int product, *prod;

typedef int time;

#ifndef ELEM
typedef product ELEMENT_TYPE;
#define ELEM
#endif

#include "../../Stack.h"

typedef stk_arr Cupboard;
```

同时我们对于货架的操作，是由时间继续调控的，认为时间为0是结束，而时间小于0则是取货物。

| time | 标识                       | 操作                                |
| ---- | -------------------------- | ----------------------------------- |
| <0   | 作为提取操作的行为标识使用 | 当输入的time<0时，进行一次提取操作  |
| =0   | 作为程序的终止标识使用     | 这个时候我们认为跳出循环            |
| >0   | 作为货物的时间标识使用     | 我们向货架内部压入一个id=time的货物 |

### 2.API接口

#### `void CupboardDisplay(Cupboard);`

展示函数，用于显示现在货架上的内容。

| param    | type     | description |
| -------- | -------- | ----------- |
| Cupboard | Cupboard | 显示对象    |
| returns  | void     |             |

#### `ELEMENT_TYPE GetLatest(Cupboard);`

获取函数，获取现在货架上面的第一个元素，并且在控制台打印出来

| param    | type         | description  |
| -------- | ------------ | ------------ |
| Cupboard | Cupboard     | 使用的对象   |
| returns  | ELEMENT_TYPE | 返回顶部元素 |

#### `int StoreProduct(Cupboard, time);`

用于放入货物，特别的是，如果是满的话，就会把最久的那个替换掉。

| param    | type     | description          |
| -------- | -------- | -------------------- |
| Cupboard | Cupboard | 使用的对象           |
| time     | time     | 物品生产日期         |
| returns  | int      | 替代bool操作是否成功 |

#### `int CupboardAction(Cupboard, time);`

封装，对于time进行判断，应当执行哪一种操作。

| param    | type     | description          |
| -------- | -------- | -------------------- |
| Cupboard | Cupboard | 使用的对象           |
| time     | time     | 操作                 |
| returns  | int      | 替代bool操作是否成功 |

### 3.注意事项

- 使用构造函数构造的对象，在最后一定要使用析构函数进行撤销。
- 对于封装好的数据结构，只能同时存储一种目标数据，对于该种数据数据应当使用宏定义进行确认。
- 对于函数中的测试用主函数，需要确认是否用宏进行的保护，防止在编译时，使得内部使用不同类型的数据结构存储不同数据时，导致编译失败。

## 四、调试结果

- 因为接口封装较好，调试时未出现明显错误情况。
- 程序运行稳定性较强。

## 五、运行结果

```powershell
D:\Coding\CProjects\DataStructureImplementingC\cmake-build-debug\DataStructureImplementingC.exe
store item 1
|1      |
---------

store item 2
|1      |
|2      |
---------

store item 5
|1      |
|2      |
|5      |
---------

the cupboard is full, get item 3
store item 3
item of 1 is dropped
|2      |
|3      |
|5      |
---------

fetch, get last: 2
|3      |
|5      |
---------

fetch, get last: 3
|5      |
---------

fetch, get last: 5
---------

no products remain
---------

store item 2
|2      |
---------

store item 3
|2      |
|3      |
---------

store item 6
|2      |
|3      |
|6      |
---------

the cupboard is full, get item 2
store item 2
item of 2 is dropped
|2      |
|3      |
|6      |
---------

the cupboard is full, get item 3
store item 3
item of 2 is dropped
|3      |
|3      |
|6      |
---------

the cupboard is full, get item 7
store item 7
item of 3 is dropped
|3      |
|6      |
|7      |
---------

the cupboard is full, get item 1
store item 1
store at top, 1 is dropped
|3      |
|6      |
|7      |
---------

fetch, get last: 3
|6      |
|7      |
---------

fetch, get last: 6
|7      |
---------

store item 2
|2      |
|7      |
---------


Process finished with exit code 0

```

## 六、源代码

```c
//
// Created by Zza on 2022/4/14.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_PRODUCT_MANAGEMENT_H
#define DATASTRUCTUREIMPLEMENTINGC_PRODUCT_MANAGEMENT_H

#ifndef MAIN_FUNC
#define MAIN_FUNC
void test_main();
#endif

typedef int product, *prod;

typedef int time;

#ifndef ELEM
typedef product ELEMENT_TYPE;
#define ELEM
#endif

#include "../../Stack.h"

typedef stk_arr Cupboard;

void CupboardDisplay(Cupboard);

ELEMENT_TYPE GetLatest(Cupboard);

int StoreProduct(Cupboard, time);

int CupboardAction(Cupboard, time);

void test_main(){
    int cap = 3;
    time input[] = {1,2,5,3,-1,-1,-1,
                    -1,2,3,6,
                    2,3,7,1,
                    -14,-1,2, 0};
//    遇到0就退出, -1代表拿取

    time* cur = input;
    Cupboard store = CreateStack(cap);

    while (*cur){
        CupboardAction(store,*cur);
        CupboardDisplay(store);
        cur++;
    }

    DestroyStack(store);

}

void CupboardDisplay(Cupboard tar){
    Cupboard cache = CreateStack(tar->len);
    ELEMENT_TYPE temp;
    while (!isEmpty(tar)){
        printf("|%d\t|\n", temp = Pop(tar));
        PushBack(cache,temp);
    }
    printf("---------\n\n");
    while (!isEmpty(cache)){
        PushBack(tar, Pop(cache));
    }
    DestroyStack(cache);
}

ELEMENT_TYPE GetLatest(Cupboard tar){
    if(isEmpty(tar)){
        printf("no products remain\n");
        return -1;
    }
    ELEMENT_TYPE res = Pop(tar);
    printf("fetch, get last: %d\n", res);
    return res;
}

int StoreProduct(Cupboard cap, time tar){
    if(isFull(cap)){
        printf("the cupboard is full, get item %d\n", tar);
//        return 0;
    }
    printf("store item %d\n",tar);

    Cupboard cache = CreateStack(cap->len);
    ELEMENT_TYPE temp;

    while (!isEmpty(cap)){
        temp = Pop(cap);

        if(temp>tar){
            PushBack_static(cap, temp);
            break;
        }
        PushBack_static(cache, temp);
    }
//    PushBack(cap,temp);
    if(!PushBack_static(cap, tar)){
        printf("store at top, %d is dropped\n",tar);
    }

    while (!isEmpty(cache)){
        if(!PushBack_static(cap, temp = Pop(cache))){
            printf("item of %d is dropped\n",temp);
        }
    }

    DestroyStack(cache);
    return 1;
}

int CupboardAction(Cupboard cap, time tar){
    if(!tar)return 0;
    if(tar<0){
        GetLatest(cap);
    } else{
        StoreProduct(cap,tar);
    }
    return 1;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_PRODUCT_MANAGEMENT_H
```

## 七、总结


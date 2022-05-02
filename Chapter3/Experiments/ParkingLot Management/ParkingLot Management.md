# Parking Lot Management

## 一、需求分析

1. 问题描述：设停⻋场内是⼀个可停放n辆汽⻋的狭⻓区域，⽬只有⼀个⼤⻔可供汽⻋进出。在停⻋场内，汽⻋按到达时间的先后顺序，依次由北向南排列(假设⼤⻔在最南端，最先到达的那辆⻋停放在⻋场的最北端)。若⻋场内已停满n辆汽⻋，则后来的汽⻋只能在⻔外的便道上等候。⼀⽇有⻋开⾛，则排在便道上的第⼀辆⻋即可开⼊。当停⻋场内某辆⻋要离开时，在它之后开⼊的⻋辆必须先退出⻋场为它让路，待该⻋开出⼤⻔外，其他⻋再按原次序返回停⻋场。每辆停放在⻋场的⻋离开停⻋场时，必须按其停留时间的⻓短交费。试为停⻋场编制按上述要求进⾏管理的模拟程序。
2. 基本要求：以顺序栈模拟停⻋场，以链队列模拟便道，按照从终端读⼊的输⼊数据序列进⾏模拟管理

- 实现基本的功能，即停车等待。

- 除了基本的功能以外，还实现了不同功能的车占有不同大小空间的功能。

- 使用宏定义，进行可调性编译。

（⼆）规定
1. 输⼊的形式和输⼊值的范围：每⼀组输⼊数据包括3个数据项:汽⻋“到达”或“离去”信息、汽⻋牌
照号码及到达或离去的时刻，其中，“A”表示到达，“D”表示离去，“E”表示输⼊结束。
每次操作先输⼊字⺟A/D/E，然后输⼊⻋牌号，是int型变量；然后输⼊对应单位时间。
2. 输出的形式：对到达的⻋辆输出其停⻋位置；对离开的⻋辆输出其停留时间和停⻋费。
3. 程序所能达到的功能：对每⼀组输⼊数据进⾏操作后的输出数据为:如果是到达的⻋辆，则输出
其在停⻋场内或便道上的停⻋位置。如果是离去的⻋辆，则输出其在停⻋场内的停留时间和应交
的费⽤(在便道上停留的时间不收费)。
4. 测试数据：设n=2，输⼊数据为（‘A’，1，5）（‘A’，2，10）（‘D’，1，15）（‘A’，3， 20）
（‘A’， 4，25）（‘A’，5，30）（‘D’，2，35）（‘D’，4，40）（‘E’，0，0）。

## 二、ADT设计

### 数据结构设计

#### `Car`

基本的车辆对象，作为基本元素存放数据。

```c
typedef struct Car{
    int id;
    int time;
} Car, *pCar;
```

#### `Dispatch`

调度内容的承载体。

```c
typedef struct Dispatch{
    char act;
    int id;
    int time;
} Dispatch;
```

#### `ParkingLot`

停车场对象，用于存放复杂的数据结构

```c
typedef struct ParkingLot{
    stk Parked;
    Queue Waiting;
} ParkingLot, *pPark;

typedef struct Car{
    int id;
    int time;
#ifdef PARK_ENHANCED
//    用大小记录类型
    double type;
#endif
} Car, *pCar;
```

### 调用的数据结构

使用之前已经实现了的数据结构。

```c
#include "../../Stack.h"
#include "../../Queue.h"

#ifndef ELEM
#define ELEM
typedef pCar ELEMENT_TYPE;
#endif

#define PARK_ENHANCED
// 升级功能打开
```

## 三、使用说明

### 1.基本结构

```c
pPark InitPark(int cap);

int DestroyPark(pPark*);

pCar GetCar(Dispatch*);

void DropCar(pCar tar){free(tar);}

int Parking_Dispatch(pPark, Dispatch *);

void Display_Cur_Status(pPark);
```

#### 测试用主函数

```c
void test_main(){
//    初始化数据
    int n = 2;
    Dispatch actions[] = {
            {'A',1,5},
            {'A',2,10},
            {'D',1,15},
            {'A',3,20},
            {'A',4,25},
            {'A',5,30},
            {'D',2,35},
            {'D',4,40},
            {'E',0,0}
    };
    Dispatch *CurAct = actions;
    pPark park = InitPark(n);

    while(CurAct->act != 'E'){
        Parking_Dispatch(park, CurAct);
        Display_Cur_Status(park);
        CurAct++;
    }
    DestroyPark(&park);
}
```

### 2.API接口

#### `InitPark`

```c
pPark InitPark(int cap);
```

初始化停车场函数，返回一个动态的指针。

| param   | type | description              |
| ------- | ---- | ------------------------ |
| int cap | int  | 停车场的最大、初始化容量 |

#### `DestroyPark`

```c
int DestroyPark(pPark*);
```

停车场撤销函数，用于撤销停车场里面的结构。

| param    | type     | description                  |
| -------- | -------- | ---------------------------- |
| `pPark*` | `pPark*` | 由之前构造函数创建的动态对象 |

#### `GetCar`

```c
pCar GetCar(Dispatch*);
```

Car对象的构造函数。

| param     | type                 | description                                |
| --------- | -------------------- | ------------------------------------------ |
| Dispatch* | 指向调度数据包的指针 | 使用调度数据包内的数据进行，车辆对象的构建 |

#### `DropCar`

```c
void DropCar(pCar tar)
```

Car对象的析构函数。

| param | type   | description |
| ----- | ------ | ----------- |
| tar   | `pCar` | 析构对象    |

#### `Parking_Dispatch`

```c
int Parking_Dispatch(pPark, Dispatch *);
```

对于单次车辆进入，进行车辆调度。

| param    | type     | description                |
| -------- | -------- | -------------------------- |
| `pPark`  | `pPark`  | 进行调度的停车场结构       |
| Dispatch | Dispatch | 本次进行的调度内容的数据包 |

#### `Display_Cur_Status`

```c
void Display_Cur_Status(pPark);
```

显示函数，显示当前停车场内部的状态。

| param   | type    | description          |
| ------- | ------- | -------------------- |
| `pPark` | `pPark` | 进行调度的停车场结构 |

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

in the parking lot:
        ---------
        |car:1  |

        ---------
the queue

in the parking lot:
        ---------
        |car:1  |
        |car:2  |

        ---------
the queue
1 Car depart, time 5->15
in the parking lot:
        ---------
        |car:2  |

        ---------
the queue

in the parking lot:
        ---------
        |car:2  |
        |car:3  |

        ---------
the queue

in the parking lot:
        ---------
        |car:2  |
        |car:3  |

        |car:4  |
        ---------
the queue

in the parking lot:
        ---------
        |car:2  |
        |car:3  |

        |car:4  |
        |car:5  |
        ---------
the queue
2 Car depart, time 10->35
in the parking lot:
        ---------
        |car:3  |
        |car:4  |

        |car:5  |
        ---------
the queue
4 Car depart, time 25->40
in the parking lot:
        ---------
        |car:3  |
        |car:5  |

        ---------
the queue

Process finished with exit code 0

```



升级后：

```c
in the parking lot:
        ---------
        |car:1,Normal Car       |

        ---------
the queue

in the parking lot:
        ---------
        |car:1,Normal Car       |
        |car:2,Normal Car       |

        ---------
the queue
try to depart: 1
1 Car depart, type: Normal Car, time 5->15
try to drop: 1
drop: 1

in the parking lot:
        ---------
        |car:2,Normal Car       |

        ---------
the queue

in the parking lot:
        ---------
        |car:2,Normal Car       |

        |car:3,Passenger Car    |
        ---------
the queue

in the parking lot:
        ---------
        |car:2,Normal Car       |

        |car:3,Passenger Car    |
        |car:4,Truck    |
        ---------
the queue

in the parking lot:
        ---------
        |car:2,Normal Car       |

        |car:3,Passenger Car    |
        |car:4,Truck    |
        |car:5,Passenger Car    |
        ---------
the queue
try to depart: 2
2 Car depart, type: Normal Car, time 10->35
try to drop: 2
drop: 2

in the parking lot:
        ---------
        |car:3,Passenger Car    |

        |car:4,Truck    |
        |car:5,Passenger Car    |
        ---------
the queue
try to depart: 4
not in the park
in the parking lot:
        ---------
        |car:3,Passenger Car    |

        |car:4,Truck    |
        |car:5,Passenger Car    |
        ---------
the queue
try to drop: 3
drop: 3
try to drop: 4
drop: 4
try to drop: 5
drop: 5

Process finished with exit code 0

```



## 六、源代码

```c
//
// Created by Zza on 2022/4/14.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H
#define DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H

#define PARK_ENHANCED

#include <stdio.h>

#ifndef MAIN_FUNC
#define MAIN_FUNC
void test_main();
#endif

typedef struct Car{
    int id;
    int time;
#ifdef PARK_ENHANCED
//    用大小记录类型
    double type;
#endif
} Car, *pCar;

#ifndef ELEM
#define ELEM
typedef pCar ELEMENT_TYPE;
#endif

typedef struct Dispatch{
    char act;
    int id;
    int time;
#ifdef PARK_ENHANCED
    double type;
#endif
} Dispatch;

#include "../../Queue.h"
#ifdef PARK_ENHANCED

typedef struct ParkingCarStack {
    double cap;
    int len;
    int top;
    ELEMENT_TYPE* array;
} Stack, *stk;

stk CreateStack(int size){
    stk st = (stk) malloc(sizeof(Stack));
    st->len = size;
    st->top = 0;
    st->cap = (double)size;
    st->array = (ELEMENT_TYPE*)malloc(sizeof(int)*(size+1));
    return st;
}

int PushBack_static(stk st, ELEMENT_TYPE obj){
    st->cap -= obj->type;
    if(st->top == st->len || st->cap<0){
        st->cap += obj->type;
        return 0;
    }
    st->array[st->top++] = obj;
    return 1;
};

void DestroyStack(stk st){
    free(st->array);
    free(st);
}

ELEMENT_TYPE Pop(stk st){
    if(st->top){
        ELEMENT_TYPE obj = st->array[--(st->top)];
        st->cap += obj->type;
        return obj;
    } else{
        perror("empty");
        exit(1);
    }
}

int isEmpty(stk st) {
    if(!(st->top))st->cap = st->len;
    return !(st->top);
}

#else

#include "../../Stack.h"
typedef stk_arr stk;

#endif

typedef struct ParkingLot{
    stk Parked;
    Queue Waiting;
} ParkingLot, *pPark;

pPark InitPark(int cap);

int DestroyPark(pPark*);

pCar GetCar(Dispatch*);

void DropCar(pCar tar){
    printf("try to drop: %d\n",tar->id);
    if(tar->id<10) {
        printf("drop: %d\n",tar->id);
        free(tar);
    }

}

int Parking_Dispatch(pPark, Dispatch *);

void Display_Cur_Status(pPark);

#ifndef PARK_ENHANCED
void test_main(){
//    初始化数据
    int n = 2;
    Dispatch actions[] = {
            {'A',1,5},
            {'A',2,10},
            {'D',1,15},
            {'A',3,20},
            {'A',4,25},
            {'A',5,30},
            {'D',2,35},
            {'D',4,40},
            {'E',0,0}
    };
    Dispatch *CurAct = actions;
    pPark park = InitPark(n);

    while(CurAct->act != 'E'){
        Parking_Dispatch(park, CurAct);
        Display_Cur_Status(park);
        CurAct++;
    }

    DestroyPark(&park);

}
#else

#define TYPE_CAR 1.0
#define TYPE_PASSENGER 1.5
#define TYPE_TRUCK 3.0

const char* GetCarType(double in){
    switch ((int)(in+0.6)) {
        case (int)(TYPE_CAR):
            return "Normal Car";
        case (int)(TYPE_PASSENGER+0.6):
            return "Passenger Car";
        case (int)(TYPE_TRUCK):
            return "Truck";
        default:
            return "not car!";
    }
}

void test_main(){
//    初始化数据
    int n = 2;
    Dispatch actions[] = {
            {'A',1,5, TYPE_CAR},
            {'A',2,10, TYPE_CAR},
            {'D',1,15},
            {'A',3,20, TYPE_PASSENGER},
            {'A',4,25, TYPE_TRUCK},
            {'A',5,30, TYPE_PASSENGER},
            {'D',2,35},
            {'D',4,40},
            {'E',0,0}
    };
    Dispatch *CurAct = actions;
    pPark park = InitPark(n);

    while(CurAct->act != 'E'){
        Parking_Dispatch(park, CurAct);
        Display_Cur_Status(park);
        CurAct++;
    }

    DestroyPark(&park);
}
#endif


pCar GetCar(Dispatch* act){
    pCar res = (pCar) malloc(sizeof(Car));
    res->id = act->id;
    res->time = act->time;
#ifdef PARK_ENHANCED
    res->type = act->type;
#endif
    return res;
}

pPark InitPark(int cap){
    pPark res = (pPark)malloc(sizeof(ParkingLot));
    res->Parked = CreateStack(cap);
    res->Waiting = QueueCreate();
    return res;
}

int DestroyPark(pPark* tar){
    while (!isEmpty((*tar)->Parked))
        DropCar(Pop((*tar)->Parked));
    while (!isEmpty_Que((*tar)->Waiting))
        DropCar(DeQueue(&((*tar)->Waiting)));

    DestroyStack((*tar)->Parked);
    QueueDestroy((*tar)->Waiting);
    free(*tar);
    *tar = NULL;
    return 1;
}

void Display_Cur_Status(pPark tar){
    stk temp_sta = CreateStack(tar->Parked->len);
    pCar temp;
    printf("\nin the parking lot:\n\t---------\n");
    while(!isEmpty(tar->Parked)){
        PushBack_static(temp_sta, Pop(tar->Parked));
    }
    while(!isEmpty(temp_sta)){
        temp = Pop(temp_sta);
#ifdef PARK_ENHANCED
        printf("\t|car:%d,%s\t|\n", temp->id, GetCarType(temp->type));
#else
        printf("\t|car:%d\t|\n", temp->id);
#endif
        PushBack_static(tar->Parked, temp);
    }

    DestroyStack(temp_sta);

    printf("\n");

    Queue que_temp = QueueCreate();

    while (!isEmpty_Que(tar->Waiting)){
        temp = DeQueue(&(tar->Waiting));
#ifdef PARK_ENHANCED
        printf("\t|car:%d,%s\t|\n", temp->id, GetCarType(temp->type));
#else
        printf("\t|car:%d\t|\n", temp->id);
#endif
        EnQueue(&que_temp,temp);
    }
    while (!isEmpty_Que(que_temp)){
        EnQueue(&(tar->Waiting), DeQueue(&que_temp));
    }
    printf("\t---------\n");
    printf("the queue\n");
    QueueDestroy(que_temp);
}

int Parking_Dispatch(pPark tar, Dispatch *actions){
    switch (actions->act) {
        case 'A':{
            if(!PushBack_static(tar->Parked, GetCar(actions))){
                EnQueue(&(tar->Waiting), GetCar(actions));
            }
            return 1;
        }
        case 'D':{
            printf("try to depart: %d\n", actions->id);
            if(isEmpty(tar->Parked)){
                return 0;
            }
            pCar temp;
            stk temp_sta = CreateStack(tar->Parked->len);
            while (!isEmpty(tar->Parked)){
                temp = Pop(tar->Parked);
                if(temp->id == actions->id){
                    break;
                } else{
                    PushBack_static(temp_sta, temp);
                }
            }
            while (!isEmpty(temp_sta))
                PushBack_static(tar->Parked, Pop(temp_sta));

            if(temp->id == actions->id){
#ifdef PARK_ENHANCED
                printf("%d Car depart, type: %s, time %d->%d\n", temp->id, GetCarType(temp->type), temp->time, actions->time);
#else
                printf("%d Car depart, time %d->%d", temp->id, temp->time, actions->time);
#endif
                DropCar(temp);

                if(!isEmpty_Que(tar->Waiting)){
                    PushBack_static(tar->Parked, DeQueue(&(tar->Waiting)));
                }
                return 1;

            } else{
                printf("not in the park");
                return 0;
            }
            }
    }
    return 0;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H

```

## 七、总结

实现了基本的调度功能，并且将详细过程做了较好的显示。

同时实现了带有类型的车辆管理模型。

- 在本次报告书写过程中，开始体会到报告并⾮做完实验书写，⽽是边编写程序边写报告。
- 对问题的分析得到相应的数据结构的选择；对设计的讨论得到代码判断的条件；通过主程序流程图的绘制把握函数的设计。
- 在完成实验完善报告时，⼜能发现代码中的不⾜与可提升之处。
- ⽐如数据结构的选择：除了题中的提示外，便道⽤循环队列实现，可以很好的解决⻋从便道离开的问题，不应局限于此。

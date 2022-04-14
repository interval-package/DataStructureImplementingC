# Parking Lot Management

## 一、需求分析

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
    sta Parked;
    Queue Waiting;
} ParkingLot, *pPark;
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

使用构造函数构造的对象，在最后一定要使用析构函数进行撤销。

## 四、调试结果

因为接口封装较好，调试时未出现明显错误情况。

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



## 六、源代码

```c
//
// Created by Zza on 2022/4/14.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H
#define DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H

#ifndef MAIN_FUNC
#define MAIN_FUNC
#endif

typedef struct Car{
    int id;
    int time;
} Car, *pCar;


#ifndef ELEM
#define ELEM
typedef pCar ELEMENT_TYPE;
#endif

typedef struct Dispatch{
    char act;
    int id;
    int time;
} Dispatch;

#include "../../Stack.h"
#include "../../Queue.h"

typedef struct ParkingLot{
    sta Parked;
    Queue Waiting;
} ParkingLot, *pPark;

pPark InitPark(int cap);

int DestroyPark(pPark*);

pCar GetCar(Dispatch*);

void DropCar(pCar tar){free(tar);}

int Parking_Dispatch(pPark, Dispatch *);

void Display_Cur_Status(pPark);

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

pCar GetCar(Dispatch* act){
    pCar res = (pCar) malloc(sizeof(Car));
    res->id = act->id;
    res->time = act->time;
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
        DropCar(OutQueue(&((*tar)->Waiting)));
    DestroyStack((*tar)->Parked);
    QueueDestroy((*tar)->Waiting);
    free(*tar);
    *tar = NULL;
    return 1;
}

void Display_Cur_Status(pPark tar){
    sta temp_sta = CreateStack(tar->Parked->len);
    pCar temp;
    printf("\nin the parking lot:\n\t---------\n");
    while(!isEmpty(tar->Parked)){
        PushBack_sta(temp_sta, Pop(tar->Parked));
    }
    while(!isEmpty(temp_sta)){
        temp = Pop(temp_sta);
        printf("\t|car:%d\t|\n", temp->id);
        PushBack_sta(tar->Parked,temp);
    }
    DestroyStack(temp_sta);

    printf("\n");

    Queue que_temp = QueueCreate();

    while (!isEmpty_Que(tar->Waiting)){
        temp = OutQueue(&(tar->Waiting));
        printf("\t|car:%d\t|\n", temp->id);
        QueueJoin(&que_temp,temp);
    }
    while (!isEmpty_Que(que_temp)){
        QueueJoin(&(tar->Waiting), OutQueue(&que_temp));
    }
    printf("\t---------\n");
    printf("the queue\n");
    QueueDestroy(que_temp);
}

int Parking_Dispatch(pPark tar, Dispatch *actions){
    switch (actions->act) {
        case 'A':{
            if(isFull(tar->Parked)){
                QueueJoin(&(tar->Waiting), GetCar(actions));
            } else{
                PushBack_sta(tar->Parked,GetCar(actions));
            }
            return 1;
        }
        case 'D':{
            if(isEmpty(tar->Parked)){
                return 0;
            }
            pCar temp;
            sta temp_sta = CreateStack(tar->Parked->len);
            while (!isEmpty(tar->Parked)){
                temp = Pop(tar->Parked);
                if(temp->id == actions->id){
                    break;
                } else{
                    PushBack_sta(temp_sta,temp);
                }
            }
            printf("%d Car depart, time %d->%d", temp->id, temp->time, actions->time);
            DropCar(temp);
            while (!isEmpty(temp_sta))PushBack_sta(tar->Parked, Pop(temp_sta));
            if(!isEmpty_Que(tar->Waiting)){
                PushBack_sta(tar->Parked, OutQueue(&(tar->Waiting)));
            }
            return 1;
        }
    }
    return 0;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H
```

## 七、总结


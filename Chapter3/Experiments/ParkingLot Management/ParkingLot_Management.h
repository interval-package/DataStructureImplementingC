//
// Created by Zza on 2022/4/14.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H
#define DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H

#define PARK_ENHANCED

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

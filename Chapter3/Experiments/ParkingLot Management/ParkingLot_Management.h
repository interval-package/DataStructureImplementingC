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

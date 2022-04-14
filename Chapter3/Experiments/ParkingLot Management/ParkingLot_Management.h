//
// Created by Zza on 2022/4/14.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H
#define DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H

typedef struct Car{
    int id;
    int time;
} Car, *pCar;

typedef Car ELEMENT_TYPE;
#ifndef ELEM
#define ELEM
#endif

typedef struct ParkingLot{

} ParkingLot, *pPark;

typedef struct Dispatch{
    char act;
    int id;
    int time;
} Dispatch;

#include "../../Stack.h"

int Parking_Dispatch(pPark, Dispatch *);

void Display_Cur_Status(pPark);

pPark InitPark();

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
    pPark park = InitPark();

    while(CurAct->act != 'E'){
        Parking_Dispatch(park, CurAct);
        Display_Cur_Status(park);
        CurAct++;
    }
}

int Parking_Dispatch(pPark tar, Dispatch *actions){

}

#endif //DATASTRUCTUREIMPLEMENTINGC_PARKINGLOT_MANAGEMENT_H

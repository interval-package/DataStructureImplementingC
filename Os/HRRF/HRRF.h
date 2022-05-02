//
// Created by Zza on 2022/4/13.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HRRF_H
#define DATASTRUCTUREIMPLEMENTINGC_HRRF_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define TIME_SLICE 10

typedef struct ProcessInfo{
    char name;
    int enter;
    int need;
    int done;
} pInfo;

#ifndef ELEM
#define ELEM
typedef pInfo ELEMENT_TYPE;
#endif

#include "../../Chapter2/LinkedList.h"

double CalcHRRF(pInfo* tar, int cur){
    return (cur - tar->enter)/tar->need;
}

void HRRF_Main(){

}


#endif //DATASTRUCTUREIMPLEMENTINGC_HRRF_H

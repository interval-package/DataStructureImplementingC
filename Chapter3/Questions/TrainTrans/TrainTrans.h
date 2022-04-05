//
// Created by Zza on 2022/4/5.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_TRAINTRANS_H
#define DATASTRUCTUREIMPLEMENTINGC_TRAINTRANS_H

#include <stdbool.h>
#include "../../Stack.h"

bool TrainTrans(const int *seq, int len){
    sta temp = CreateStack(len);
    bool flag = true;
    int i=1, j=0;
    while(i<=len && j<len){
        if(i<seq[j]){
            PushBack(temp, i++);
        }
        else if(i == seq[j] || Pop(temp) == seq[j]){
            i++;
            j++;
        }
        else{
            flag = false;
            break;
        }
    }
    DestroyStack(temp);
    return flag;
}

void main_train(){
    int tar_1[] = {4,3,5,6,1,2};
    int tar_2[] = {1,3,5,4,2,6};
    printf("%d\n", TrainTrans(tar_1,6));
    printf("%d\n", TrainTrans(tar_2,6));
}


#endif //DATASTRUCTUREIMPLEMENTINGC_TRAINTRANS_H

//
// Created by Zza on 2022/4/1.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_SELFDIVIDENUMBERS_H
#define DATASTRUCTUREIMPLEMENTINGC_SELFDIVIDENUMBERS_H

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdbool.h>
#include <stdlib.h>

bool isSelfDivide(int num);

int* selfDividingNumbers(int left, int right, int* returnSize){
    int *output = (int*)malloc(sizeof(int)*(right-left+1));
    *returnSize = 0;
    for(int i = left; i<=right; i++){
        if(isSelfDivide(i)){
            output[(*returnSize)++] = i;
        }
    }
    return output;
}

bool isSelfDivide(int num){
    int iter ,temp = num;
    do{
        iter = temp%10;
        if(iter == 0 || num%iter != 0)return false;
        temp /= 10;
    } while (temp);
    return true;
}


#endif //DATASTRUCTUREIMPLEMENTINGC_SELFDIVIDENUMBERS_H

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

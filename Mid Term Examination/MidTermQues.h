//
// Created by Zza on 2022/4/13.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_MIDTERMQUES_H
#define DATASTRUCTUREIMPLEMENTINGC_MIDTERMQUES_H

// ques 1
#include "../Chapter2/Sequential_List.h"
typedef SequentialList SeqList;
typedef ELEMENT_TYPE DataType;
int ListLength(SeqList L);
int ListGet(SeqList, int i, DataType *x);

int ListFindMinMax(SeqList L, int* Min, int* Max){
    int temp, len = ListLength(L);
    if(len<1){
        return 0;
    }
    ListGet(L, 0, Max);
    ListGet(L, 0, Min);
    for(int i=0;i<len;i++){
        ListGet(L, i, &temp);
        *Max = temp>*Max?temp:*Max;
        *Min = temp<*Min?temp:*Min;
    }
    return 1;
}

// ques 2
#include "../Chapter3/Stack.h"

int Stack_Delete_ByX(sta obj, ELEMENT_TYPE tar){
    sta buf = CreateStack(obj->len);
    ELEMENT_TYPE temp;
    while(!isEmpty(obj)){
        tar == (temp = Pop(obj)) ? 0 : PushBack(buf, temp);
    }
    while (!isEmpty(buf)){
        PushBack(obj, Pop(buf));
    }
    DestroyStack(buf);
    return 1;
}


#endif //DATASTRUCTUREIMPLEMENTINGC_MIDTERMQUES_H

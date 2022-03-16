//
// Created by 86189 on 2022/3/8.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_SEQUENTIAL_LIST_H
#define DATASTRUCTUREIMPLEMENTINGC_SEQUENTIAL_LIST_H

#include <error.h>
#include <stdlib.h>
#define INIT_LEN 100
#define INCREMENT 10
typedef int ELEMENT_TYPE;

typedef struct {
    ELEMENT_TYPE *elementArray;
    int elementCount;
    int totalElemSize;
} SequentialList;

// declare
#define IS_FULL_SQLIST(p) (p)->elementCount==(p)->totalElemSize

#define IS_EMPTY_SQLIST(p) (P)->elementCount==0

int SequentialListInit(SequentialList *La);

int SequentialListDestruct(SequentialList *La);

int sqListIncrease(SequentialList *La, int times);

void sqListInsert(SequentialList *La,int pos,ELEMENT_TYPE tar);

void sqListPushBack(SequentialList *La,ELEMENT_TYPE tar);

int compare_basic_int(ELEMENT_TYPE elem_1,ELEMENT_TYPE elem_2);

void LocateEveryElements(SequentialList *La, SequentialList *Lb,
                         ELEMENT_TYPE,int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE));

int CalcRepetitionMaxOnly(SequentialList *La,int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE));

void CalcDatumRepetitionMax(SequentialList*,SequentialList*,int(*compare_int)(ELEMENT_TYPE, ELEMENT_TYPE));

int LocateFirstElem_LowEndSentry(SequentialList *La,ELEMENT_TYPE tar,
                                 int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE));

void SortSqlist(SequentialList *La,int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE));

// define
int SequentialListInit(SequentialList *La){
// 在初始化时使用n+1个元素，0号位存放哨兵元素
    ELEMENT_TYPE* tempPointer = (ELEMENT_TYPE*)malloc((INIT_LEN+1)*sizeof(ELEMENT_TYPE));
    if(tempPointer == NULL){
        perror("init memory malloc failed");
        La->elementArray = NULL;
        exit(EXIT_FAILURE);
    }
    La->elementArray = tempPointer;
    La->elementCount = 0;
    La->totalElemSize = INIT_LEN;
    return 1;
}

int SequentialListDestruct(SequentialList *La){
    free(La->elementArray);
    La->elementArray = NULL;
    La->elementCount = 0;
// 用总长-1来表示已经进行了释放
    La->totalElemSize = -1;
    return 1;
}

int sqListIncrease(SequentialList *La, int times){
//    re allocate memory
    ELEMENT_TYPE *tempPointer = (ELEMENT_TYPE*)realloc(La->elementArray,
                                         (La->totalElemSize+1+times*INCREMENT)*sizeof(ELEMENT_TYPE));
    if(tempPointer == NULL){
        perror("increase failed");
        return 0;
    }
    La->elementArray = tempPointer;
    La->totalElemSize += times*INCREMENT;
    return 1;
}

void sqListInsert(SequentialList *La,int pos,ELEMENT_TYPE tar){
//    界限保护
    if(pos < 1 || pos > La->elementCount+1){
        perror("argument pos exceed");
        return;
    }
    if(IS_FULL_SQLIST(La)){
        (void)sqListIncrease(La,1);
    }
    int end = La->elementCount+1;
// 逆向移开元素
    while(end > pos){
        La->elementArray[end] = La->elementArray[end-1];
        end--;
    }
    La->elementArray[pos] = tar;
    La->elementCount++;
}

void sqListPushBack(SequentialList *La,ELEMENT_TYPE tar){
    if(IS_FULL_SQLIST(La)){
        (void)sqListIncrease(La,1);
    }
    La->elementArray[++(La->elementCount)] = tar;
}

int compare_basic_int(ELEMENT_TYPE elem_1,ELEMENT_TYPE elem_2){
    return elem_1-elem_2;
}

// using sequential list to contain the result
void LocateEveryElements(SequentialList *La, SequentialList *Lb,
                         ELEMENT_TYPE  tar,
                         int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE))
{
//    Lb should be an empty sqList
    if(Lb->elementCount == 0){
        perror("the Lb should be an empty sqList, please configure and retry");
        return;
    }
//    这里先把Element type默认为int了，要是做类型模板C语言很麻烦
    for(int i=1;i<=La->elementCount;i++){
        if(!compare_int(La->elementArray[i],tar))
            sqListPushBack(Lb,i);
    }
}

int CalcRepetitionMaxOnly(SequentialList *La,int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE)){//    对线性表进行排序，变成有序表
    SortSqlist(La,compare_int);
    int temp = 0, tar = 0;
    for(int i=1,count=0;i<La->elementCount;i++){
        count++;
//        当前与下一个元素进行对比，如果相同，compare返回0，则计数加一
        if(compare_int(La->elementArray[i],La->elementArray[i+1])){
//            如果与下一元素不相同，则count与temp进行比较，如果count>temp，则用count赋值temp
            if(count>temp){
                temp=count;
//                将该连续元素的位置记录
                tar = i;
            }
            count=0; // clear count
        }else{
        count++;
        }
    }
//    用0号位放目标元素的值
    La->elementArray[0] = La->elementArray[tar];
    return temp;
}

void CalcDatumRepetitionMax(SequentialList *La,SequentialList *Lb,int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE))
{
    //    Lb should be an empty sqList
    if(Lb->elementCount == 0){
        perror("the Lb should be an empty sqList, please configure and retry");
        return;
    }
//    现在有的问题就是，只能找出一个最大的，要怎么找出所有最大的数
    int window = CalcRepetitionMaxOnly(La,compare_int);
// 由上面的算法，我们可以得到最多数量的元素的数量,同时也对La完成了排序
// 将其设置为窗口长度，从线性表一端滑动到结尾，步长为1，如果窗口开始和结尾相同，那么窗口中元素为目标元素
    int i = 1;
    while(i+window-1<=La->elementCount){
        if(La->elementArray[i]==La->elementArray[i+window-1]){
            sqListPushBack(Lb,La->elementArray[i]);
            i++;
        }
    }
}

// 使用低端哨兵方法查找
int LocateFirstElem_LowEndSentry(SequentialList *La,ELEMENT_TYPE tar,int(*compare_int)(ELEMENT_TYPE,ELEMENT_TYPE)){
// 获取末尾指针
    ELEMENT_TYPE *pArray = &(La->elementArray[La->elementCount]);
// 初始化哨兵0位
    La->elementArray[0] = tar;
    int i = La->elementCount;
    while(compare_int(tar,*pArray--))--i;
    return i;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_SEQUENTIAL_LIST_H

//
// Created by Zza on 2022/3/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "./SortByAccessFrequency.h"

// 基本算法思想：向后遍历至目标位置，摘下结点，向前遍历，到合适位置插入

// 按照给出的元素数组初始化链表
DuList InitList(ELEMENT_TYPE *array, int len){
//    预设头结点
    DuList res = (DuList) malloc(sizeof(DuNode));
//    这里先预设头节点后继为自己，放在temp里面
    DuNode *temp = res, *p = res;
//    头节点的freq设置为-1，这个很重要
    res->freq = -1;
    res->len = len;
    res->prior = NULL;
    for(int i=1; i<=len;i++,array++){
        temp = (DuList) malloc(sizeof(DuNode));
        temp->data = *array;
        temp->freq = 0;
        p->rear = temp;
        temp->prior = p;
        p=temp;
    }
    temp->rear = NULL;
    return res;
}

void DestroyList(DuList l){
    DuNode *p;
    while (l->rear){
        p = l->rear;
        free(l);
        l = p;
    }
}

void ShowListInfo(DuList la,int axis){
    if(axis){
        printf("value\tfreq\n");
        while (la->rear){
            la = la->rear;
            printf("%d\t%d\n",la->data,la->freq);
        }
    } else{
        DuList temp = la;
        printf("value:");
        while (la->rear){
            la = la->rear;
            printf("\t%d",la->data);
        }
        printf("\nfreq:");
        while (temp->rear){
            temp = temp->rear;
            printf("\t%d",temp->freq);
        }
        printf("\n");
    }
}

struct PosContainer AccessElement(DuList p, ELEMENT_TYPE tar){
    struct PosContainer res;
    int i = 0;
//    防止找到的是最后一个元素而跳出
    int flag = 0;
    while(p->rear){
//        先进行指针和序号的移动
        i++;
        p = p->rear;
        if(p->data == tar){
//            访问到达，频率+1，flag设置为1
            flag = 1;
            p->freq++;
            break;
        }
    }
    if(!flag){   // 只有flag为1找到，没有找到的输出
        res.before = -1;
        return res;
    }

    res.before = i;
//    摘下p结点
//    保留元素值
    DuNode *temp = p;
//    拆链
    p->prior->rear = p->rear;
    if(p->rear)p->rear->prior = p->prior;
//    前向遍历
    while(p->prior){
//        先将指针前移
        p=p->prior;
        if(p->freq>=temp->freq){
//            若所指处的的freq比原来值的freq小或者相等，p则指在了前驱上
//            所有的freq都一定会比头节点的freq大，
            break;
        }
//        后--，那么现在就是直接指在了目标位上了
        i--;
    }
    res.now = i;
//    插入
    temp->prior = p;
    temp->rear = p->rear;
    if(p->rear)p->rear->prior =temp;
    p->rear = temp;
    return res;
}

#define VALUE_LEN 10
#define REQUEST_TIME 1000

void SortByFreq_main(){
    srand((unsigned)time(NULL));

    int ValueList[VALUE_LEN];
    for(int i=0;i<VALUE_LEN;i++)ValueList[i]=i;
    int RequestList[REQUEST_TIME];
    for(int i=0;i<REQUEST_TIME;i++)RequestList[i] = rand()%(VALUE_LEN);

    DuList tar = InitList(ValueList,VALUE_LEN);

    struct PosContainer pos;

    printf("original:\n");
    ShowListInfo(tar,0);


    for(int i=0;i<REQUEST_TIME;i++){
        pos = AccessElement(tar,RequestList[i]);
        if(i%200==0) {
            printf("\ni:%d pos:%d, %d\n", i, pos.before, pos.now);
            ShowListInfo(tar,0);
        }
    }

    printf("\nafter:\n");
    ShowListInfo(tar,0);
}

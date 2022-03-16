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
//    两种方式显示数组的内容
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
    DuNode *temp = p;   // 保留元素值
//    拆链
    p->prior->rear = p->rear;
    if(p->rear)p->rear->prior = p->prior;   // 不管是插入还是删除都要注意前后结点是否为空
//    前向遍历
    while(p->prior){
        p=p->prior; // 先将指针前移
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
    if(p->rear)p->rear->prior =temp;//    不管是插入还是删除都要注意前后结点是否为空
    p->rear = temp;
    return res;
}

// 被访问数组的长度
#define VALUE_LEN 10
// 访问事件表的长度
#define REQUEST_TIME 1000
// 错误数据的数量
#define BAD_NUMS 2

// 测试用主函数
void SortByFreq_main(){
    srand((unsigned)time(NULL));

//    初始化数据列表
    int ValueList[VALUE_LEN];
    for(int i=0;i<VALUE_LEN;i++)ValueList[i]=i;
//    初始化访问列表
    int RequestList[REQUEST_TIME];
    for(int i=0;i<REQUEST_TIME;i++)RequestList[i] = rand()%(VALUE_LEN);
//    设计超出区间值
    for(int i=0;i<BAD_NUMS;i++)RequestList[rand()%REQUEST_TIME] = rand()%(VALUE_LEN)+VALUE_LEN;

//    初始化列表
    DuList tar = InitList(ValueList,VALUE_LEN);

    struct PosContainer pos;

    printf("original:\n");
    ShowListInfo(tar,0);

//    开始事件测试
    for(int i=0;i<REQUEST_TIME;i++){
        pos = AccessElement(tar,RequestList[i]);
        if(pos.before<0)printf("\nexceeding at i=%d, with %d\n",i, RequestList[i]);
        if(i%400==0) {
            printf("\ni:%d pos:%d, %d\n", i, pos.before, pos.now);
            ShowListInfo(tar,0);
        }
    }

    printf("\nafter:\n");
    ShowListInfo(tar,0);
}

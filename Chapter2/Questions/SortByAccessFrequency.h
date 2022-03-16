//
// Created by Zza on 2022/3/16.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_SORTBYACCESSFREQUENCY_H
#define DATASTRUCTUREIMPLEMENTINGC_SORTBYACCESSFREQUENCY_H

typedef int ELEMENT_TYPE;

// 双链表就可以了，不一定要循环
typedef struct Container_DoublyLinkedListNode{
    struct Container_DoublyLinkedListNode *prior, *rear;
    union {
        ELEMENT_TYPE data;
        int len;
    };
    int freq;
} DuNode, *DuList;

// 用来存放当前查找位置的返回值，变化前和变化后
struct PosContainer{
    int before;
    int now;
};

DuList InitList();

void DestroyList(DuList);

// 只是定义一下，还是先不使用了
int Compare_ByValue();
int Compare_ByFreq();

// 会对原表进行修改
struct PosContainer AccessElement(DuList, ELEMENT_TYPE);

// 不设置输入参数了
void SortByFreq_main();

// 要有两个链表，一个是访问序列，一个是存储序列

// 想法1：使用被访问的向前移动的思想

#endif //DATASTRUCTUREIMPLEMENTINGC_SORTBYACCESSFREQUENCY_H

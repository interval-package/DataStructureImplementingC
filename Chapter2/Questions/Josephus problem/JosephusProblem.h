//
// Created by 86189 on 2022/3/19.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_JOSEPHUSPROBLEM_H
#define DATASTRUCTUREIMPLEMENTINGC_JOSEPHUSPROBLEM_H

#include <stdlib.h>
#define JOSEPHUS_LEN 500

typedef struct JosephusCircle{
    int pos;
    struct JosephusCircle *next;
} *jCircle, jNode;

jCircle jCircleInit(int len){
//    不设置头结点
    jCircle temp, head, p = (jCircle)malloc(sizeof(jNode));
    head = p;
//    pos 从1开始
    p->pos = 1;
    for(int i=1; i<len; i++){
        temp = (jCircle)malloc(sizeof(jNode));
        temp->pos = i+1;
        p->next = temp;
        p = temp;
    }
//    形成闭环
    temp->next = head;
    return head;
}

int JosephusProblem(jCircle jc,int step,int pos){
    int count = 0;
//    先将光标移动到目标位置
    while(jc->pos != pos){
        jc = jc->next;
    }
    jCircle temp;
    while(jc->next != jc){
//        进行循环计数
        count = (count+1)%(step+1);
        if(count == step) {
//            如果计数到达步长,则释放结点
            temp->next = jc->next;
            free(jc);
            jc = temp->next;
            continue;
        }
        temp = jc;
        jc = jc->next;
    }
//    循环至只有最后一个结点
    return jc->pos;
}


// JosephusProblem using regression
int f(int n, int m){
    return n == 1 ? n : (f(n - 1, m) + m - 1) % n + 1;
}

//对于每一次处决,我们认为都使得总长度-1,然后使得我们的编号重新排序一次.
//新编号new,就编号old,则有old = (new+m)%n.
//为了补正序号从0开始,old = (new+m-1)%n + 1
//f(1,m)=1,到达最后只有一个人的时候,结束.

#endif //DATASTRUCTUREIMPLEMENTINGC_JOSEPHUSPROBLEM_H

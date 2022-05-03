//
// Created by Zza on 2022/5/3.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_BFS_H
#define DATASTRUCTUREIMPLEMENTINGC_BFS_H

#include "../Graph.h"

// in this case we assume to use the adjacent list

bool BFS_ListComponent(AdjListGraph* tar,int i,int* visited);

bool BFS_AdjListGraph(AdjListGraph* tar);

// BFS would use the que

bool BFS_ListComponent(AdjListGraph* tar,int i,int* visited){
    int len = tar->nums;
    int *que = (int*)malloc(sizeof(int)*len);

    int head = 0 ,tail;

    que[tail++] = i;

    int node;

    while ((tail - head)%len){
        node = que[++head];

    }
    return true;
};

#endif //DATASTRUCTUREIMPLEMENTINGC_BFS_H

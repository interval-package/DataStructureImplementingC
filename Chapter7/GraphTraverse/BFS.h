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
    int len = tar->nums + 1;
    int *que = (int*)malloc(sizeof(int)*(len));

    int head = 0 ,tail = 0;

    que[tail++] = i;

    int node;

    arc tempArc;

    while ((tail - head + len)%len){
        node = que[head];
        head = (head+1)%len;
        visited[node] = 1;
        tempArc = tar->List[node].first;
        while (tempArc){
            if(!visited[tempArc->adjVex]){
                visited[tempArc->adjVex] = 1;
                que[tail] = tempArc->adjVex;
                tail = (tail+1)%len;
            }
            tempArc = tempArc->next;
        }
    }
    return true;
};

#endif //DATASTRUCTUREIMPLEMENTINGC_BFS_H

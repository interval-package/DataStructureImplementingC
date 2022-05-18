//
// Created by Zza on 2022/5/3.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_DFS_H
#define DATASTRUCTUREIMPLEMENTINGC_DFS_H

#include "../Graph.h"
#include <stdbool.h>

bool DFS_Mat(mGraph*,int,int*);

bool DFS_Mat(mGraph* tar,int start ,int* visited){
    int *stack = (int*) malloc(sizeof(int)*tar->vNums);
    int top = 0, cur = start, temp;
    stack[top++] = start;
    visited[cur] = 1;
    while (top){
        temp = cur;
        for (int i = 0; i < tar->vNums; ++i) {
            if(!visited[i] && tar->adjacentMat[cur][i]<INF){
//                search deeper
                stack[top++] = i;
//                update current pos, together visit it
                printf("%d-(%d)>%d",cur,tar->adjacentMat[cur][i],i);
                cur = i;
                visited[cur] = 1;
                break;
            }
        }
        if(temp==cur){
//            判断是否进行了下一步的深入，如果没有深入，则返回一格
            cur = stack[--top];
        }
    }

    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_DFS_H

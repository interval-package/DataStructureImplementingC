//
// Created by Zza on 2022/5/6.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_KRUSKALALGORITHM_H
#define DATASTRUCTUREIMPLEMENTINGC_KRUSKALALGORITHM_H

#include "../Graph.h"

// 无论如何，我们都使用双亲表示法进行树结构的存储

#include <stdbool.h>

bool TupleSorter(Edge_Tuple*, int);

// 有一个前提，必须是连通图，不然会把空边给连上

bool Kruskal(mGraph* tar){

    int* AdjVertexes = (int*)malloc(tar->vNums*sizeof(int));

    int* forest = (int*)malloc(tar->vNums*sizeof(int));

    Edge_Tuple* edges = (Edge_Tuple*)malloc(tar->vNums*tar->vNums*sizeof(int));

    for(int i=0,j;i<tar->vNums;i++){
        forest[i] = -1;
        AdjVertexes[i] = -1;
        for(j=0;j<tar->vNums;j++){
            edges[i*tar->vNums+j].head = i;
            edges[i*tar->vNums+j].rear = j;
            edges[i*tar->vNums+j].weight = tar->adjacentMat[i][j];
        }
    }

    TupleSorter(edges,tar->vNums);

    int root_1, root_2;

    for (int i=0, j=0; i < tar->vNums-1; ++i, ++j) {
        root_1 = edges[j].head;
        root_2 = edges[j].rear;
//        回溯集合根
        while (forest[root_1]>0){
            root_1 = forest[root_1];
        }
//        回溯集合根
        while (forest[root_2]>0){
            root_1 = forest[root_2];
        }
        if (root_1 == root_2){
//            判断为同集合，判断下一条边
            i--;
        } else{
//            记录边-记录边标号
//            AdjVertexes[i] = j;
//            记录边-亲子方式记录
            AdjVertexes[edges->rear] = edges->head;
//            合并集合
            forest[root_1] = root_2;
        }
    }
    free(edges);
    free(forest);
    free(AdjVertexes);
    return true;
}

bool TupleSorter(Edge_Tuple* tar, int pos){
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_KRUSKALALGORITHM_H

//
// Created by Zza on 2022/4/29.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_GRAPH_H
#define DATASTRUCTUREIMPLEMENTINGC_GRAPH_H

#include <stdlib.h>
#include <stdbool.h>

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

typedef struct Graph_Matrix{
    int vNums;
    ELEMENT_TYPE *vertexes;
    int** adjacentMat;
} mGraph;

bool Construct_mGraph(mGraph*,int);

bool Destruct_mGraph(mGraph*);

bool Construct_mGraph(mGraph* graph,int nums){
    graph->vNums = nums;
    graph->vertexes = (ELEMENT_TYPE*) malloc(sizeof(ELEMENT_TYPE)*nums);
    graph->adjacentMat = (int**) malloc(sizeof (int*)*nums);
    for(int i=0;i<nums;i++){
        graph->adjacentMat[i] = (int*) malloc(sizeof (int)*nums);
    }
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_GRAPH_H

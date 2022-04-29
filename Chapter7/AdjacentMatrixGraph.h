//
// Created by Zza on 2022/4/29.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_ADJACENTMAXTRIXGRAPH_H
#define DATASTRUCTUREIMPLEMENTINGC_ADJACENTMAXTRIXGRAPH_H

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

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

bool GetAdjacent(mGraph*, int nodePos);

bool Construct_mGraph(mGraph* graph,int nums){
    graph->vNums = nums;
    graph->vertexes = (ELEMENT_TYPE*) malloc(sizeof(ELEMENT_TYPE)*nums);
    graph->adjacentMat = (int**) malloc(sizeof (int*)*nums);
    for(int i=0;i<nums;i++){
//        calloc would init with default value of 0
        graph->adjacentMat[i] = (int*) calloc(nums,sizeof(int));
    }
    if(errno){
        perror("Construct mGraph fail");
        return false;
    }
    return true;
}

bool Destruct_mGraph(mGraph* graph){
    free(graph->vertexes);
    for(int i=0;i<graph->vNums;i++){
//        calloc would init with default value of 0
        free(graph->adjacentMat[i]);
    }
    free(graph->adjacentMat);
    if(errno){
        perror("Destruct mGraph fail");
        return false;
    }
    return true;
}



#endif //DATASTRUCTUREIMPLEMENTINGC_ADJACENTMAXTRIXGRAPH_H

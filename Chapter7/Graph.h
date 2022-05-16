//
// Created by Zza on 2022/4/29.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_GRAPH_H
#define DATASTRUCTUREIMPLEMENTINGC_GRAPH_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define INF 999

#define MAX_WEIGHT 255

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

typedef struct Edge_Tuple{
    int head;
    int rear;
    int weight;
}Edge_Tuple;

//======================================================================================================================
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
    for(int i=0, j;i<nums;i++){
        graph->adjacentMat[i] = (int*) malloc(sizeof (int)*nums);
        for(j=0;j<nums;j++){
            graph->adjacentMat[i][j] = INF;
        }
    }
    return true;
}

bool Destruct_mGraph(mGraph* tar){
    for(int i=0;i<tar->vNums;i++){
        free(tar->adjacentMat[i]);
    }
    free((tar->adjacentMat));
    free(tar->vertexes);
    return true;
}

bool Disp_mGraph(const mGraph* tar){
    printf("#\t");
    for(int i=0; i<tar->vNums; i++){
        printf("%d\t", i);
    }
    for(int i=0; i<tar->vNums; i++){
        printf("%d:\t",i);
        for (int j = 0; j < tar->vNums; ++j) {
            printf("%d\t", tar->adjacentMat[i][j]);
        }
        printf("\n");
    }
    return true;
}

//======================================================================================================================

typedef struct ArcNode {
   int adjVex;
   union {
       int mark;
   };
    int weight;
   struct ArcNode* next, *sub;
} ArcNode, *arc;

typedef struct ArcPack{
    int i,j;
    int weight;
} ArcPack;

typedef struct VexNode {
    char elem;
    int len;
    arc first;
} VexNode, *vex;

typedef struct AdjListGraph {
    int nums;
    vex List;
} AdjListGraph;

// 实际上我也不知道该用什么形式，进行初始化
bool Init_AdjListGraph(AdjListGraph* tar, int len){
    tar->nums = len;
    tar->List = (vex) calloc(len,sizeof(VexNode));
    return true;
}

bool AddArc_AdjListGraph(AdjListGraph* tar, ArcPack _Arc){
//    deep copy the _Arc
    arc temp = (arc) malloc(sizeof(ArcNode));
    temp->next = tar->List[_Arc.i].first;
    temp->adjVex = _Arc.j;
    temp->weight = _Arc.weight;
    tar->List[_Arc.i].first = temp;
    return true;
}

bool Disp_adjList_graph(const AdjListGraph* tar){
    arc temp;
    for(int i=0; i<tar->nums; i++){
        printf("%d:\t",i);
        temp = tar->List[i].first;
        while (temp){
            printf("-(%d)>%d\t",temp->weight,temp->adjVex);
            temp = temp->next;
        }
        printf("\n");
    }
    return true;
}

//======================================================================================================================

bool Add_Tree_Arc_Mat(mGraph* tar, Edge_Tuple info){
    tar->adjacentMat[info.rear][info.head] = info.weight;
    return true;
}

// actually we have two method of add tree nodes
bool Add_Tree_Arc_List(AdjListGraph* tar, Edge_Tuple info){
    arc temp = malloc(sizeof(ArcNode));
    temp->weight = info.weight;
    temp->adjVex = info.head;
    temp->next = tar->List[info.rear].first->next;
    tar->List[info.head].first = temp;
    return true;
}

//======================================================================================================================

#endif //DATASTRUCTUREIMPLEMENTINGC_GRAPH_H

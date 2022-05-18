//
// Created by Zza on 2022/5/17.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H
#define DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H

#include "../../GraphTraverse/BFS.h"
#include "../../GraphTraverse/DFS.h"

// generate interface

#define V_NUMS 8

void traverse_main(){
//    初始化图结构
    mGraph d_graph;
    AdjListGraph b_graph;

    Construct_mGraph(&d_graph,V_NUMS);
    Init_AdjListGraph(&b_graph,V_NUMS);

    Edge_Tuple init[]={
            {0,1,2},
            {6,0,3},
            {1,2,2},
            {2,5,10},
            {5,7,6},
            {7,6,1},
            {0,6,1},
            {6,3,5},
            {3,1,4},
            {4,1,1},
            {1,4,3},
            {4,3,2},
            {3,4,7},
            {4,6,8},
            {0,7,4},
            {-1,-1,0}
    };
    Edge_Tuple* temp = init;
    while (temp->weight){
//        构建图
        Add_Tree_Arc_List(&b_graph,*temp);
        Add_Tree_Arc_Mat(&d_graph,*temp);
        temp++;
    }

    int* vis[V_NUMS];

    DFS_Mat(&d_graph,0,(int*)vis);

}


#endif //DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H

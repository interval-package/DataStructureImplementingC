//
// Created by Zza on 2022/5/16.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_EXP_MST_H
#define DATASTRUCTUREIMPLEMENTINGC_EXP_MST_H

#include "../../Graph.h"
#include "../../MinimumCostSpanningTree/PrimAlgorithm.h"
#include "../../MinimumCostSpanningTree/KruskalAlgorithm.h"

#define VEX_NUM 8

void Mst_main_prim(){
    AdjListGraph map;
    int *res;
    Init_AdjListGraph(&map,VEX_NUM);
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
        Add_Tree_Arc_List(&map,*temp);
        temp++;
    }
    Disp_adjList_graph(&map);
    prim(&map,1,&res);
    Disp_prim_res(&map,res);
}


#endif //DATASTRUCTUREIMPLEMENTINGC_EXP_MST_H

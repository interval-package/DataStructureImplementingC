//
// Created by Zza on 2022/5/6.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_PRIMALGORITHM_H
#define DATASTRUCTUREIMPLEMENTINGC_PRIMALGORITHM_H

#include "../Graph.h"
#include <stdlib.h>
// using adj list

bool Search_Min(const int* arr, const bool* vis, int len, int* res);

void Disp_prim_temp_int(int*tar, int len);

void Disp_prim_temp_bool(bool*tar, int len);

bool prim(AdjListGraph* tar, int start, int** res){
    int* low_cost = malloc(sizeof(int)*tar->nums);
    int* adj_vex = malloc(sizeof(int)*tar->nums);
    bool* vis = malloc(sizeof(bool)*tar->nums);
//    初始化
    for(int i = 0;i<tar->nums;i++){
        low_cost[i] = INF;
        adj_vex[i] = start;
        vis[i] = false;
    }
    vis[start] = true;
    int temp;
    arc temp_arc;
    temp_arc = tar->List[start].first;
    while (temp_arc){
        low_cost[temp_arc->adjVex] = temp_arc->weight;
        temp_arc = temp_arc->next;
    }

    for(int _timer = 0; _timer<tar->nums; _timer++){
        Disp_prim_temp_bool(vis, tar->nums);
        Disp_prim_temp_int(low_cost,tar->nums);
        Disp_prim_temp_int(adj_vex,tar->nums);

        Search_Min(low_cost,vis,tar->nums,&temp);
//        先找到目前集到
        vis[temp] = true;
//        跟新对外环境
        temp_arc = tar->List[start].first;
        while (temp_arc){

            if(!vis[temp_arc->adjVex] && temp_arc->weight < low_cost[temp_arc->adjVex]){
                adj_vex[temp_arc->adjVex] = temp;
                low_cost[temp_arc->adjVex] = temp_arc->weight;
            }
            temp_arc = temp_arc->next;
        }
    }

    free(low_cost);
    *res = adj_vex;
    free(vis);
    return true;
}

bool Search_Min(const int* arr, const bool* vis, int len, int* res){
    int temp = INF;
    for (int i = 0; i < len; ++i) {
        if(!vis[i]){
            if(arr[i]<temp){
                temp = arr[i];
            }
        }
    }
    *res = temp;
    return true;
}

void Disp_prim_temp_bool(bool*tar, int len){

}

void Disp_prim_temp_int(int*tar, int len){

}

void Disp_prim_res(AdjListGraph* tar, int start, int** res){

}

#endif //DATASTRUCTUREIMPLEMENTINGC_PRIMALGORITHM_H

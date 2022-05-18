//
// Created by Zza on 2022/5/17.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H
#define DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H

#include "../../GraphTraverse/BFS.h"
#include "../../GraphTraverse/DFS.h"

// generate interface

void bfs_main();
void dfs_main();

void traverse_interface(){
    printf("here is the traverse mode, with commands\n"
           "1: into the bfs mode\n"
           "2: into the dfs mode\n"
           );

    int opt;
    scanf("%d",&opt);
    switch (opt) {
        case 1:{
            bfs_main();
            break;
        }
        case 2:{
            dfs_main();
            break;
        }
        default:{
            break;
        }
    }
}

//
#define V_NUMS 8

void bfs_main(){
    int temp;
    printf("input vex nums: ");
    scanf("%d",&temp);
    Edge_Tuple data;
    AdjListGraph obj;
    Init_AdjListGraph(&obj, temp);
    printf("input in rear head weight, end with weight<0:\n");
    while (scanf("%d %d %d",data.rear,data.head, data.weight)){
        if(data.weight<0)break;
        Add_Tree_Arc_List(&obj,data);
    }
    printf("input root: ");
    scanf("%d",&temp);
    Disp_adjList_graph(&obj);
    int *vis = malloc(sizeof(int)*obj.nums);
    for (int i = 0; i < obj.nums; ++i) {
        vis[i] = 0;
    }
    BFS_ListComponent(&obj,temp,vis);
    Destruct_adjList_graph(&obj);
    free(vis);
}

void dfs_main(){
    int temp;
    printf("input vex nums: ");
    scanf("%d",&temp);
    Edge_Tuple data;
    mGraph obj;
    Init_mGraph(&obj, temp);
    printf("input in rear head weight, end with weight<0:\n");
    while (scanf("%d %d %d",data.rear,data.head, data.weight)){
        if(data.weight<0)break;
        Add_Tree_Arc_Mat(&obj,data);
    }
    printf("input root: ");
    scanf("%d",&temp);
    Disp_mGraph(&obj);
    int *vis = malloc(sizeof(int)*obj.vNums);
    for (int i = 0; i < obj.vNums; ++i) {
        vis[i] = 0;
    }
    DFS_Mat(&obj,temp,vis);
    Destruct_mGraph(&obj);
    free(vis);
}

void traverse_main(){
//    初始化图结构
    mGraph d_graph;
    AdjListGraph b_graph;

    Init_mGraph(&d_graph, V_NUMS);
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
            {1,2,12},
            {1,4,3},
            {4,3,2},
            {2,6,3},
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

    int vis[V_NUMS];
    for (int i = 0; i < V_NUMS; ++i) {
        vis[i] = 0;
    }

    Disp_mGraph(&d_graph);
    DFS_Mat(&d_graph,0,vis);


    for (int i = 0; i < V_NUMS; ++i) {
        vis[i] = 0;
    }
    Disp_adjList_graph(&b_graph);
    BFS_ListComponent(&b_graph,0,vis);

    Destruct_mGraph(&d_graph);
    Destruct_adjList_graph(&b_graph);
}


#endif //DATASTRUCTUREIMPLEMENTINGC_EXP_TRAVERSE_H

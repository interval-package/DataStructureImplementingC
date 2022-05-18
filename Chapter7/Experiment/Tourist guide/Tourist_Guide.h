//
// Created by Zza on 2022/5/17.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_TOURIST_GUIDE_H
#define DATASTRUCTUREIMPLEMENTINGC_TOURIST_GUIDE_H

#include "../../Graph.h"
#include "../../MinimumLengthPath/FloydAlgorithm.h"
#include "../../MinimumLengthPath/Hamiltonian_Algorithm.h"
#include "../Traveling Salesman Problem/TSP_dynamic_planning.h"

//======================================================================================================================
// interface functions

int Tourist_guide_interface();

void Tourist_guide_actions();

void Tourist_show_map();

//======================================================================================================================
// kernel functions

// get the min path, using the floyd

// Traveling salesman problem



//======================================================================================================================
//tourist guide main

#define VEX_NUM 5

void touring(){
    int opt;
    mGraph obj;
    int path[N];
    int dp[N][M];
    int g[N][N] = {
            {INF,3,INF,8,9},
            {3,INF,3,10,5},
            {INF,3,INF,4,3},
            {8,3,INF,4,3},
            {9,5,3,20,INF}
    };
    TSP_Dynamic(dp, g);

    Init_mGraph(&obj, N);

    copy_mat_mGraph((int**)g,N,&obj);

    opt = Tourist_guide_interface();

    switch (opt) {
        case 1:{
            Disp_mGraph(&obj);
            break;
        }
        case 2:{
            printf("please input your destination: ");
            scanf("%d",&opt);
//            解析Floyd矩阵

            break;
        }
        case 3:{
            printf("sad");
            break;
        }
        default:{
            printf("undef command\n");
        }
    }
}

//======================================================================================================================
int Tourist_guide_interface(){
    int res;

    printf("commands:\n"
           "1: show graph\n"
           "2: show min path\n"
           "3: show routine\n");

    scanf("%d",&res);
    return res;
}

//======================================================================================================================


#endif //DATASTRUCTUREIMPLEMENTINGC_TOURIST_GUIDE_H

//
// Created by Zza on 2022/5/17.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_TSP_H
#define DATASTRUCTUREIMPLEMENTINGC_TSP_H

#include "../../Graph.h"

#define N 2
#define M 4

//核心函数，求出动态规划dp数组
void TSP(int** dp, int** g){
    //初始化dp[i][0]
    for(int i = 0 ; i < N ;i++){
        dp[i][0] = g[i][0];
    }
    //求解dp[i][j],先跟新列在更新行
    for(int j = 1 ; j < M ;j++){
        for(int i = 0 ; i < N ;i++ ){
            dp[i][j] = INF;
            //如果集和j(或状态j)中包含结点i,则不符合条件退出
            if( ((j >> (i-1)) & 1) == 1){
                continue;
            }
            for(int k = 1 ; k < N ; k++){
                if( ((j >> (k-1)) & 1) == 0){
                    continue;
                }
                if( dp[i][j] > g[i][k] + dp[k][j^(1<<(k-1))]){
                    dp[i][j] = g[i][k] + dp[k][j^(1<<(k-1))];
                }
            }
        }
    }

}

#endif //DATASTRUCTUREIMPLEMENTINGC_TSP_H

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
// dp为返回参数
// g 为我们已经有的路径数组

    // 初始化dp[i][0]
    for(int i = 0 ; i < N ;i++){
        dp[i][0] = g[i][0];
    }
    // 求解dp[i][j],先更新列再更新行
    for(int j = 1 ; j < M ;j++){
        for(int i = 0 ; i < N ;i++ ){
//            先假定自己到达这个集为不可能
            dp[i][j] = INF;
            // 如果集和j(或状态j)中包含结点i,则不符合条件退出
            if( ((j >> (i-1)) & 1) == 1){
                continue;
            }
//            取最小的子
            for(int k = 1 ; k < N ; k++){
                if( ((j >> (k-1)) & 1) == 0){
//                    如果j中无k
                    continue;
                }
                if( dp[i][j] > g[i][k] + dp[k][j^(1<<(k-1))] ){
//                    j^(1<<(k-1))表示将1移到第k位，也就是指向只有k元素的这个集，然后异或，表示剔除这个k
//                    也就是构造 cij = cik + dp{j - k}
                    dp[i][j] = g[i][k] + dp[k][j^(1<<(k-1))];
                }
            }
        }
    }
}



#endif //DATASTRUCTUREIMPLEMENTINGC_TSP_H

//
// Created by Zza on 2022/5/17.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_TSP_DYNAMIC_PLANNING_H
#define DATASTRUCTUREIMPLEMENTINGC_TSP_DYNAMIC_PLANNING_H

#include "../../Graph.h"

#define N 5
static const int M = 1 << (N-1);

//static int dp[N][M];

//核心函数，求出动态规划dp数组
void TSP_Dynamic(int dp[N][M], int g[N][N]){
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


// 判断结点是否都以访问,不包括0号结点
bool isVisited(const bool* visited){
    for(int i = 1 ; i < N ;i++){
        if(visited[i] == false){
            return false;
        }
    }
    return true;
}


//获取最优路径，保存在path中,根据动态规划公式反向找出最短路径结点
void getPath(int dp[N][M], int g[N][N],int path[N]){
    //标记访问数组
    bool visited[N] = {false};
    //前驱节点编号
    int pioneer = 0 ,min = INF, S = M - 1, temp ;
    //把起点结点编号加入容器
    int top = 0;
    path[top++] = 0;

    while(!isVisited(visited)){
        for(int i=1; i<N;i++){
            if(visited[i] == false && (S & (1<<(i-1))) != 0){
                if(min > g[i][pioneer] + dp[i][(S^(1<<(i-1)))]){
                    min = g[i][pioneer] + dp[i][(S^(1<<(i-1)))] ;
                    temp = i;
                }
            }
        }
        pioneer = temp;
        path[top++] = pioneer;
        visited[pioneer] = true;
        S = S ^ (1<<(pioneer - 1));
        min = INF;
    }
}
// 输出路径

void printPath(int path[N]){
    printf("the route: ");
    for (int i = 0; i < N; ++i) {
        printf("-->%d",path[i]);
    }
}

int tsp_main_dym()
{
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
    printf("the min is %d\n",dp[0][M-1]);
    getPath(dp,g,path);
    printPath(path);
    return 0;
}



#endif //DATASTRUCTUREIMPLEMENTINGC_TSP_DYNAMIC_PLANNING_H

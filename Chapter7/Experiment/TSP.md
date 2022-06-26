# TSP

这个问题是当初图论的时候自己写的，没有在`oj`网站上进行测评。

## 前言

TSP问题是广为人知的组合优化问题，它易于描述，但是难以求解。基于TSP问题的特性，决定使用通过TSP问题来学习各类启发算法，比较不同启发算法在旅行商问题上的表现。

## 问题

TSP问题可以描述为：现有一些节点，节点和节点之间均可相连形成边，节点之间的边存在距离，需要找到一个遍历方案先后访问所有的点，使的遍历的总距离最短。

#### 数据结构

使用整数表示集合：

$9 = 1001 = \{4,1\}$

- 对于第y个城市，他的二进制表达为，1<<(y-1)。
- 对于数字x，要看它的第i位是不是1，那么可以通过判断布尔表达式 (((x >> (i - 1) ) & 1) == 1或者（x  & (1<<(i-1))）!= 0的真值来实现。
- 由动态规划公式可知，需要从集合中剔除元素。假如集合用索引x表示，要剔除元素标号为i,我们异或运算实现减法，其运算表示为： x = x ^ (1<<(i - 1))。

## 基本算法

### TSP_Dynamic

动态规划：$d(i,V) = min({C_{ik}+d(k,V-(K))})$

基本上算法思路就是：

1. 我们站在一个点上，我们知道我们到达原点的距离
2. 对于我们来说，有一片没有访问的点构成点集$V$
3. 对于我们接下来要走的路径，就是对这个$V$求最优解
4. 找的这个最优的解，以及初始点$k$
5. 我们接下来要到达要进入这个点集，通过临近自己的一个点$k$
6. 我们到了这个点k，我们要对$V-\{K\}$，再次求解

我们先计算$dp[N][M]$数组之后，我可以用dp数组来反向推出其路径。其算法思想如下：

- 比如在第一步时，我们就知道那个值最小

- 因为dp[][]数组我们已经计算出来了，由计算可知C01+d(1,{2,3,4})最小，所以一开始从起始点0出发，经过1。接下来同样计算d(1,{2,3,4})

- 由计算可知C14+d(4,{2,3})所以0--->1---->4，接下来同理求d(4,{2,3})，这里就省略。最终计算出来的路径为：0--->1--->4--->2--->3--->0

![](D:\Coding\CProjects\DataStructureImplementingC\Pics\Display_pics\Chapter7\TSP.png)

## 解决

```c
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

    printf("the min is %d\n",dp[0][M-1]);
    getPath(dp,g,path);
    printPath(path);
    return 0;
}



#endif //DATASTRUCTUREIMPLEMENTINGC_TSP_DYNAMIC_PLANNING_H
```
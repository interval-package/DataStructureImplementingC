//
// Created by Zza on 2022/5/6.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_DIJKSTRAALGORITHM_H
#define DATASTRUCTUREIMPLEMENTINGC_DIJKSTRAALGORITHM_H

#include "../Graph.h"

bool Dijkstra(mGraph* tar, int source){
    int* Dist = (int*) malloc(sizeof(int)*tar->vNums);
    int* Path = (int*) malloc(sizeof(int)*tar->vNums);
    bool* Mark = (bool*) malloc(sizeof(bool)*tar->vNums);

//    init
    for (int i = 0; i < tar->vNums; ++i) {
        Dist[i] = tar->adjacentMat[source][i];
        Path[i] = source;
        Mark[i] = false;
    }
    Mark[source] = true;

    int AddNode;
    for (int i = 0; i < tar->vNums; ++i) {
//        找到未在集内的距离最短点
        for (int j = 0, minDis = INF; j < tar->vNums; ++j) {
            if(!Mark[j] && Dist[j]<minDis){
                minDis = Dist[j];
                AddNode = j;
            }
        }

//        加入点
        Mark[AddNode] = true;

//        修改最短点引入影响
        for (int j = 0; j < tar->vNums; ++j) {
//            实际上这里可以不用判断在不在集内，因为我们默认到集内点一定是最短了的，后面比较一定能排除
            if(!Mark[j] && Dist[AddNode]+tar->adjacentMat[AddNode][j] < Dist[j]){
//                修改离集距离
                Dist[j] = Dist[AddNode]+tar->adjacentMat[AddNode][j];
//                记录路径
                Path[j] = AddNode;
            }
        }
    }

    free(Mark);
    free(Dist);
    free(Path);

    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_DIJKSTRAALGORITHM_H

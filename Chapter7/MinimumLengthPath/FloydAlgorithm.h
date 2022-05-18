//
// Created by Zza on 2022/5/6.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_FLOYDALGORITHM_H
#define DATASTRUCTUREIMPLEMENTINGC_FLOYDALGORITHM_H

#include "../Graph.h"


bool CopyPathMat(mGraph* tar, int** newMat);

bool CopyDistMat(mGraph* tar, int** newMat);

bool DesMat(int** tarMat, int);

bool Floyd(mGraph* tar){

//    路径矩阵
    int** paths;
//    相对距离矩阵
    int** dist;

    CopyPathMat(tar,paths);
    CopyDistMat(tar,dist);
//        循环层1，选择中介节点
    for(int i=0;i<tar->vNums;i++){
//            循环层2、3，遍历矩阵
        for(int j=0;j<tar->vNums;j++)
            for(int k=0;k<tar->vNums;k++)
//                如果当前两点距离，经过i会缩短的话
                if(dist[j][k]> dist[j][i]+dist[i][k]){
//                    更新最短距离
                    dist[j][k] = dist[j][i]+dist[i][k];
//                    更新中间经过的节点
                    paths[j][k] = i;
                }
    }

    DesMat(paths,tar->vNums);
    DesMat(dist,tar->vNums);
    return true;
}

bool Solve_Floyd(int** mat, int start, int end){
    return true;
}

bool CopyDistMat(mGraph* tar, int** newMat){
    newMat = (int**)malloc(sizeof(int*)*tar->vNums);
    for (int i = 0; i < tar->vNums; ++i) {
        newMat[i] = (int*)malloc(sizeof(int)*tar->vNums);
        for (int j = 0; j < tar->vNums; ++j) {
            newMat[i][j] = tar->adjacentMat[i][j];
        }
    }
    return true;
}

bool CopyPathMat(mGraph* tar, int** newMat){
    newMat = (int**)malloc(sizeof(int*)*tar->vNums);
    for (int i = 0; i < tar->vNums; ++i) {
        newMat[i] = (int*)malloc(sizeof(int)*tar->vNums);
        for (int j = 0; j < tar->vNums; ++j) {
//            初始化，有直接相连边记为本身，如果没有直接相互连边，则记为-1
            newMat[i][j] = tar->adjacentMat[i][j]<MAX_WEIGHT?i:-1;
        }
    }
    return true;
}

bool DesMat(int** tarMat, int nums){
    for (int i = 0; i < nums; ++i) {
        free(tarMat[i]);
    }
    free(tarMat);
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_FLOYDALGORITHM_H
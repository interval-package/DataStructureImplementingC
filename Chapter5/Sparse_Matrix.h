//
// Created by 86189 on 2022/4/2.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_SPARSE_MATRIX_H
#define DATASTRUCTUREIMPLEMENTINGC_SPARSE_MATRIX_H

#include <stdlib.h>

typedef struct tri_tuple{
    int col, row;
    int val;
}tri_tuple, *tri_tu;

typedef struct Sparse_Matrix{
    int len;
    int col_len;
    int row_len;
    tri_tu list;
//    head node exist
} Sparse_Matrix, *Sp_Mat;

void CalcColNums(const Sparse_Matrix *tar,int *output){
    for(int i=1;i<=output[0];i++)output[i]=0;
    for(int i=0;i<tar->len;i++)output[tar->list[i].col]++;
    for(int i=2;i<=output[0];i++){
        output[i] = output[i-1]+output[i];
    }

}

// 实际上这里要承认，没有设计好，应该永头结点存结构数据的，但是没有，所以头结点设立了，但是没有什么用

// test require
// 这个算是很重要的算法了，要怎么去跳转
void Transpose(Sp_Mat tar){
    tri_tu list = (tri_tu)malloc(sizeof(tri_tuple)*tar->len);
    int *nums = (int*)malloc(sizeof(int)*(tar->col_len+1));
    nums[0] = tar->col_len;
    CalcColNums(tar,nums);
    int pos;
    for(int i=1;i<=tar->len;i++){
        pos = tar->list[i].col;
        pos = nums[pos]++;
        list[pos].col = tar->list[i].row;
        list[pos].row = tar->list[i].col;
        list[pos].val = tar->list[i].val;
    }
    pos = tar->col_len;
    tar->col_len = tar->row_len;
    tar->row_len = pos;
    tar->list = list;
    free(nums);
}



#endif //DATASTRUCTUREIMPLEMENTINGC_SPARSE_MATRIX_H

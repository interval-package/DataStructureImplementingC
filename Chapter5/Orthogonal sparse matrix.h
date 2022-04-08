//
// Created by Zza on 2022/4/8.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_ORTHOGONAL_SPARSE_MATRIX_H
#define DATASTRUCTUREIMPLEMENTINGC_ORTHOGONAL_SPARSE_MATRIX_H

// Orthogonal list

#include <stdlib.h>
typedef struct Orthogonal_Node{
    int row, col, data;
    struct Orthogonal_Node* p_col, *p_row;
} Orthogonal_Node, *OrtNode;

typedef OrtNode OrtMat;

OrtMat OrtMatCreate(int row, int col){
    OrtMat res = (OrtNode)malloc(sizeof(Orthogonal_Node));
    res->row = row;
    res->col = col;
    res->data = 0;

    OrtNode temp = res;
    for(int i=0;i<row;i++){
        temp->p_row = (OrtNode)malloc(sizeof(Orthogonal_Node));
        temp = temp->p_row;
        temp->p_col = temp;
        temp->row = i+1;
        temp->col = 0;
        temp->data = 0;
    }
    temp->p_row = res;

    temp = res;
    for(int i=0;i<col;i++){
        temp->p_col = (OrtNode)malloc(sizeof(Orthogonal_Node));
        temp = temp->p_col;
        temp->p_row = temp;
        temp->col = i+1;
        temp->row = 0;
        temp->data = 0;
    }
    temp->p_col = res;
    return res;
}


#endif //DATASTRUCTUREIMPLEMENTINGC_ORTHOGONAL_SPARSE_MATRIX_H

//
// Created by Zza on 2022/4/27.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_MODIFYTREELEAVES_H
#define DATASTRUCTUREIMPLEMENTINGC_MODIFYTREELEAVES_H

#include "BinTreeUtils.h"

bool CalcTreeLeaves(pTreeNode tar, int* nums){
    *nums = 0;
    pTreeNode temp;
    _TreeQue que;
    _tree_init_que(&que);
    _tree_que_en(&que,tar);
    while (!_tree_que_isEmpty(&que)){
        _tree_que_de(&que,&temp);
        if(temp->left || temp->right){
            if(temp->left){
                _tree_que_en(&que,temp->left);
            }
            if(temp->right){
                _tree_que_en(&que,temp->right);
            }
        } else{
            (*nums)++;
        }
    }
    return true;
}

bool SwapTreeLeaves(pTreeNode tar){
    pTreeNode temp, swapper;
    _TreeQue que;
    _tree_init_que(&que);
    _tree_que_en(&que,tar);
    while (!_tree_que_isEmpty(&que)){

        _tree_que_de(&que,&temp);

        if(temp->left){
            _tree_que_en(&que,temp->left);
        }
        if(temp->right){
            _tree_que_en(&que,temp->right);
        }

        swapper = temp->left;
        temp->left = temp->right;
        temp->right = swapper;
    }
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_MODIFYTREELEAVES_H

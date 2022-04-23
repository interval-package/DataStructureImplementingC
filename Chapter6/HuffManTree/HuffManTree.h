//
// Created by Zza on 2022/4/23.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREE_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREE_H

#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "../../Chapter4/String.h"

typedef struct node{
    char tar;
    int freq;
} node;

#ifndef ELEM
#define ELEM
typedef node ELEMENT_TYPE;
#endif

#include "../Binary Tree/BinaryTree_Array.h"

typedef struct HuffManTree{
//    实际上这里应该自己再重新设置一个
    Bin_Tree_Arr trees;
    int curTop;
    int treeNums;
    int* roots;
    bool encoded;
}HuffManTree;

typedef struct InitDataPackage{
    int n;
    node* init;
} pkg;

__attribute__((unused)) bool Init_HuffMan(HuffManTree* tar, pkg* info);

__attribute__((unused)) bool HuffManEncoding(HuffManTree* tar);

__attribute__((unused)) bool HuffManDecoding(HuffManTree* obj, char tar, pStr res);

__attribute__((unused)) bool HuffManDecodeDisplay(Bin_Tree_Arr obj, int root);

//======================================================================================================================

bool _find_two_min_tree(HuffManTree* tar, int *min1, int *min2);

bool _tree_merge(HuffManTree* tar, int root1, int root2);

//======================================================================================================================

__attribute__((unused)) bool HuffManEncoding(HuffManTree* tar){
    int timer = tar->treeNums - 1;
    int cur_tree_l, cur_tree_r;
    while (timer--){
//        找到最小的两个树，在roots中的位置
        _find_two_min_tree(tar,&cur_tree_l,&cur_tree_r);
//        认为左结点会比右结点小，将树拼接，然后结点坐标存在roots的右边
        _tree_merge(tar,cur_tree_l,cur_tree_r);
    }
    return true;
}

__attribute__((unused)) bool Init_HuffMan(HuffManTree* tar, pkg* info){
    BinStaticTree_init(tar->trees, 2*info->n+1);
    tar->treeNums = tar->curTop = tar->trees->cur =info->n;
    tar->roots = (int*) malloc(sizeof(int)*info->n);
    for(int i=0;i<info->n;i++){
        tar->trees->elems[i].data = info->init[i];
        tar->trees->elems[i].left = tar->trees->elems[i].right = -1;
        tar->roots[i]=-1;
    }
    tar->encoded = false;
    return true;
}

//======================================================================================================================

bool _find_two_min_tree(HuffManTree* tar, int *min1, int *min2){
//    由于我们算法的设计，我们认为，0号位置一定会在交归纳中是最后一个树的根，用这个来预设
    *min1, *min2 = 0;
    int temp;
//    root负责记录是树根的结点位置
    for(int i=1, j=0;i<tar->treeNums;i++){
        temp = tar->roots[i];
        if(tar->roots[i]>=0){
            temp = tar->trees[temp].elems->data.freq;
            if(temp <= tar->trees[tar->roots[*min2]].elems->data.freq){
                if(temp < tar->trees[tar->roots[*min2]].elems->data.freq){
                    *min2 = *min1;
                    *min1 = i;
                } else{
                    *min2 = i;
                }
            }
        }
    }
    tar->encoded = true;
    return true;
}

bool _tree_merge(HuffManTree* tar, int root_l, int root_r){
    node l, r, cur;
    l = tar->trees[tar->roots[root_l]].elems->data;
    r = tar->trees[tar->roots[root_r]].elems->data;

    _StaticNode temp = {{l.tar,l.freq + r.freq},tar->roots[root_l], tar->roots[root_r]};

    *(tar->trees[tar->curTop].elems) = temp;

    tar->roots[root_l] = tar->curTop;
    tar->roots[root_r] = -1;

    tar->curTop++;
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREE_H

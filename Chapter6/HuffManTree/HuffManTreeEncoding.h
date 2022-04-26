//
// Created by Zza on 2022/4/23.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEENCODING_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEENCODING_H

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

bool DisplayHuffManStruct(HuffManTree*);

__attribute__((unused)) bool PkgDestruct(pkg*);

__attribute__((unused)) bool Init_HuffMan(HuffManTree* tar, pkg* info);

__attribute__((unused)) bool HuffManEncoding(HuffManTree* tar);

bool HuffManDestruct(HuffManTree *tar);

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
    tar->trees = (Binary_Tree_Array*)malloc(sizeof(Binary_Tree_Array));
    BinStaticTree_init(tar->trees, 2*info->n+1);
    tar->treeNums = tar->curTop = tar->trees->cur =info->n;
    tar->roots = (int*) malloc(sizeof(int)*info->n);
    for(int i=0;i<info->n;i++){
        tar->trees->elems[i].data = info->init[i];
        tar->trees->elems[i].left = tar->trees->elems[i].right = -1;
        tar->roots[i]=i;
    }
    tar->encoded = false;
    return true;
}

//======================================================================================================================

bool _find_two_min_tree(HuffManTree* tar, int *min1, int *min2){
//    由于我们算法的设计，我们认为，0号位置一定会在交归纳中是最后一个树的根，用这个来预设
    *min1 = *min2 = 0;
    int temp;
//    root负责记录是树根的结点位置
    for(int i=1, j=0;i < tar->treeNums;i++){
        temp = tar->roots[i];
        if(temp>=0){
            temp = tar->trees->elems[temp].data.freq;
            if(temp <= tar->trees->elems[tar->roots[*min2]].data.freq){
                if(temp < tar->trees->elems[tar->roots[*min1]].data.freq){
                    *min2 = *min1;
                    *min1 = i;
                } else{
                    *min2 = i;
                }
            }
        }
    }
    return true;
}

bool _tree_merge(HuffManTree* tar, int root_l, int root_r){
    node l, r, cur;

    l = tar->trees->elems[tar->roots[root_l]].data;
    r = tar->trees->elems[tar->roots[root_r]].data;

    tar->trees->elems[tar->roots[root_l]].parent = tar->trees->elems[tar->roots[root_r]].parent = tar->curTop;

//    printf("merge %d,%d at %d,%d\n",root_l,root_r,tar->roots[root_l],tar->roots[root_r]);
//    printf("with char: %c,%c\n",l.tar,r.tar);
//    printf("with freq: %d,%d\n",l.freq,r.freq);

    _StaticNode temp = {{'s',l.freq + r.freq},tar->roots[root_l], tar->roots[root_r]};
    
    tar->trees->elems[tar->curTop] = temp;

    tar->roots[root_l] = tar->curTop;
    tar->roots[root_r] = -1;

    tar->curTop++;
    return true;
}

bool HuffManDestruct(HuffManTree *tar){
    BinStaticTree_destruct(tar->trees);
    free(tar->trees);
    free(tar->roots);
}



#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEENCODING_H

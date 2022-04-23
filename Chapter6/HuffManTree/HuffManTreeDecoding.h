//
// Created by Zza on 2022/4/23.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H

#include "./HuffManTree.h"

__attribute__((unused)) bool HuffManDecoding(HuffManTree* obj, char tar, pStr res);

#ifndef TREE_STK
#define TREE_STK
typedef int tNode;
#endif

// 我们应当好好利用哈夫曼树是一个完全二叉树的性质来进行解码
// 那么对于我们的编码长度，实际上是可以预测的吧
__attribute__((unused)) bool HuffManDecodeDisplay(Bin_Tree_Arr obj, int root){
    char* routine = (char*) malloc(sizeof(char)*obj->cur);
    int i, n = obj->cur;
    while (n--){
        i = 0;
        while (obj->elems[root].left > 0){
            routine[i++] = '0';
        }
    }
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H

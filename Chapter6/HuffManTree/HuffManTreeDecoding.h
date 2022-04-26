//
// Created by Zza on 2022/4/23.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H

#include "./HuffManTreeEncoding.h"

__attribute__((unused)) bool HuffManDecoding(HuffManTree* obj, char tar, pStr res);

#ifndef TREE_STK
#define TREE_STK
typedef int tNode;
#endif

bool DisplayAct(char*, int, char);

// 我们应当好好利用哈夫曼树是一个完全二叉树的性质来进行解码
__attribute__((unused)) bool HuffManDecodeDisplay(Bin_Tree_Arr obj, int root){
//    设置两个栈，一个栈用来存我们的行动路径，一个栈拿来存上一个根节点
    char* routine = (char*) malloc(sizeof(char)*obj->cur);
    int* nodes = (int*) malloc(sizeof(int)*obj->cur);

    int i = 0, n = obj->cur;
//    总共访问n个叶子
    while (n--){
//        向左下搜索到最下方
        while (obj->elems[root].left > 0){
            nodes[i] = root;
            routine[i++] = '0';
            root = obj->elems[root].left;
        }
//        显示当前编码路径
        DisplayAct(routine,i,obj->elems[root].data.tar);

//        向上退栈
// 首先，我们在路径栈中，存放的是我们以什么方式来到这个节点
// 如果我们是由向右操作，进入节点的话，说明我们已经访问过这个根的子树，应当再次向上
        do {
            root = nodes[--i];
//            每次路径退栈，也是反映我们是从左还是右回溯进入根的
        }while (routine[i+1] == '1');
//        当我们一直向上走，如果我们是从左进入根时，认为左树遍历完成，我们就会退出循环，去访问右边
//        向右移动一次
        root = obj->elems[root].right;
        nodes[i] = root;
        routine[i++] = '1';
    }
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H

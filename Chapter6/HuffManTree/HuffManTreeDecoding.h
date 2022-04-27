//
// Created by Zza on 2022/4/23.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H

#include "./HuffManTreeEncoding.h"

#define HUFFMAN_CODE_NUMS 10
#define HUFFMAN_CODE_BASE_CHAR '0'

typedef struct ResContainer{
    char* res[HUFFMAN_CODE_NUMS];
}ResContainer;

bool ContainerDestruct(ResContainer*);

bool DisplayContainer(ResContainer*);

__attribute__((unused)) bool HuffManDecode_Display_Stack(HuffManTree* tar, int root);

bool HuffManDecode_Reverse(HuffManTree* tar, ResContainer*);

#ifndef TREE_STK
#define TREE_STK
typedef int tNode;
#endif

bool DisplayAct(char*, int, char);

// 我们应当好好利用哈夫曼树是一个完全二叉树的性质来进行解码
__attribute__((unused)) bool HuffManDecode_Display_Stack(HuffManTree* tar, int root){
    Bin_Tree_Arr obj = tar->trees;
//    设置两个栈，一个栈用来存我们的行动路径，一个栈拿来存上一个根节点

    char* routine = (char*) malloc(sizeof(char)*obj->cur);
    int* nodes = (int*) malloc(sizeof(int)*obj->cur);

    char act;

    int i = 0, n = tar->treeNums;
//    总共访问n个叶子
    while (n){
//        向左下搜索到最下方

        printf("-----------------------\n"
               "left searching, start root %d l:%d r:%d\n",
               root,obj->elems[root].left,obj->elems[root].right);

        while (root>=0 && obj->elems[root].left >= 0){
            printf("%d-",root);
            nodes[i] = root;
            routine[i++] = '0';
            root = obj->elems[root].left;
        }
//        显示当前编码路径
        DisplayAct(routine,i,obj->elems[root].data.tar);
        n--;

//        向上退栈
// 首先，我们在路径栈中，存放的是我们以什么方式来到这个节点
// 如果我们是由向右操作，进入节点的话，说明我们已经访问过这个根的子树，应当再次向上
        do {
            if(!i)break;
            root = nodes[--i];
            act = routine[i];

//            printf("trace back,act:%c, cur root %d l:%d r:%d\n",act,root,obj->elems[root].left,obj->elems[root].right);

            //            每次路径退栈，也是反映我们是从左还是右回溯进入根的
        }while (act == '1');
//        当我们一直向上走，如果我们是从左进入根时，认为左树遍历完成，我们就会退出循环，去访问右边
//        向右移动一次

        root = obj->elems[root].right;
        nodes[i] = root;
        routine[i++] = '1';

//        printf("right move, cur root %d l:%d r:%d\n",
//               root,obj->elems[root].left,obj->elems[root].right);

    }
    return true;
}

bool HuffManDecode_Reverse(HuffManTree* tar, ResContainer* container){
    int cur,temp,base;
    for(int i=0;i<tar->treeNums;i++){
        cur = i;
        container->res[i] = (char*) malloc(sizeof(char)*tar->treeNums);
        base = tar->treeNums;
        container->res[i][--base] = '\0';
        while (tar->trees->elems[cur].parent){
            temp = tar->trees->elems[cur].parent;
            container->res[i][--base] = (cur==tar->trees->elems[temp].left)?'0':'1';
            cur = temp;
        }
        container->res[i][0] = (char)--base;
    }
    return true;
}

bool DisplayAct(char* tar, int len, char type){
    printf("huffman code %c:",type);
    for(int i=0;i<len;i++){
        printf("%c",*tar);
        tar++;
    }
    printf("\n");
}

bool ContainerDestruct(ResContainer* tar){
    for (int i = 0; i < HUFFMAN_CODE_NUMS; ++i) {
        free(tar->res[i]);
    }
    return true;
}

bool DisplayContainer(ResContainer* tar){
    for (int i = 0; i < HUFFMAN_CODE_NUMS; ++i) {
        printf("%c: %s\n",i+HUFFMAN_CODE_BASE_CHAR,&(tar->res[i][(tar->res[i][0])+1]));
    }
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREEDECODING_H

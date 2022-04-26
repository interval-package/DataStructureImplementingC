//
// Created by Zza on 2022/4/25.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREE_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREE_H

#include "HuffManTreeEncoding.h"
#include "HuffManTreeDecoding.h"

bool CalcCharFreq(const char* tar, pkg* res){
    int map[HUFFMAN_CODE_NUMS];
    for(int i=0;i<HUFFMAN_CODE_NUMS;i++){
        map[i] = 0;
    }
    while (*tar){
        map[(int)*tar-HUFFMAN_CODE_BASE_CHAR]++;
        tar++;
    }
    res->init = (node*)malloc(sizeof(node)*HUFFMAN_CODE_NUMS);
    res->n = HUFFMAN_CODE_NUMS;
    for(int i=0;i<HUFFMAN_CODE_NUMS;i++){
        res->init[i].tar = (char)(i+HUFFMAN_CODE_BASE_CHAR);
        res->init[i].freq = map[i];
    }
    return true;
}

__attribute__((unused)) bool PkgDestruct(pkg* tar){
    for(int i=0;i<tar->n;i++){
        free(tar->init);
    }
    return true;
}

bool HuffManDisplay(const char* tar){
    pkg info;
    CalcCharFreq(tar,&info);

    HuffManTree obj;
    Init_HuffMan(&obj,&info);
    HuffManEncoding(&obj);
    DisplayHuffManStruct(&obj);

//    HuffManDecode_Reverse(&obj);
    HuffManDecode_Display_Stack(&obj, obj.curTop-1);

    HuffManDestruct(&obj);
    PkgDestruct(&info);
    return true;
}

bool DisplayHuffManStruct(HuffManTree* tar){
    for(int i=0;i<tar->curTop;i++){
        _StaticNode temp = tar->trees->elems[i];
        printf("id: %d\t"
               "char: %c\t"
               "freq: %d\t"
               "left: %d\t"
               "right: %d\t"
               "parent: %d\n",i,
               temp.data.tar,temp.data.freq,temp.left,temp.right,temp.parent);
    }
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMANTREE_H

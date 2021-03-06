//
// Created by Zza on 2022/4/25.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_DISP_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_DISP_H

#include "HuffManTreeEncoding.h"
#include "HuffManTreeDecoding.h"
#include <stdio.h>

bool CalcCharFreq(const char* tar, pkg* res);
// this func will calc the freq of each char in a string

//----------------------------------------------------------------------------------------------------------------------

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

bool PkgDestruct(pkg* tar){
    free(tar->init);
    return true;
}

bool HuffManDisplay(const char* tar){
    pkg info;
    CalcCharFreq(tar,&info);

    HuffManTree obj;
    Init_HuffMan(&obj,&info);
    HuffManEncoding(&obj);
    DisplayHuffManStruct(&obj);

    ResContainer container;
    HuffManDecode_Reverse(&obj, &container);
    DisplayContainer(&container);

    HuffManDecode_Display_Stack(&obj, obj.curTop-1);


    ContainerDestruct(&container);
    HuffManDestruct(&obj);
    PkgDestruct(&info);
    return true;
}

bool DisplayHuffManStruct(HuffManTree* tar){
    for(int i=0;i<tar->curTop;i++){
        bin_tree_arr_node temp = tar->trees->elems[i];
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

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_DISP_H

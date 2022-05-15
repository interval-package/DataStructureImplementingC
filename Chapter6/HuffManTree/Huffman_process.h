//
// Created by Zza on 2022/5/15.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_PROCESS_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_PROCESS_H

#include "Huffman_output.h"

#define CODE_PATH "D:\\Coding\\CProjects\\DataStructureImplementingC\\Chapter6\\HuffManTree\\code.dat"
#define TREE_PATH "D:\\Coding\\CProjects\\DataStructureImplementingC\\Chapter6\\HuffManTree\\tree.dat"

bool Huff_Man_Generate_Write(const char* tar){
    pkg info;
    CalcCharFreq(tar,&info);

    HuffManTree obj;
    Init_HuffMan(&obj,&info);
    HuffManEncoding(&obj);
//    print the current struct of huffman

    FILE* file =  fopen(TREE_PATH,"w");
    if(file){
        Output_Huff_Body(&obj,file);
    }

    ResContainer container;
    HuffManDecode_Reverse(&obj, &container);

    FILE* file2 = fopen(CODE_PATH,"w");

    if(file2){
        Output_Encoding_Res(&container,file2);
    }

    fclose(file);
    fclose(file2);

    ContainerDestruct(&container);
    HuffManDestruct(&obj);
    PkgDestruct(&info);
    return true;
}

bool Huff_Man_Generate_Read(){
    ResContainer container;
    FILE* file_1 = fopen(CODE_PATH,"r");
    Input_Encoding_Res(&container, file_1);
    fclose(file_1);
    DisplayContainer(&container);


    HuffManTree obj;
    FILE* file =  fopen(TREE_PATH,"r");
    if(file){
        Input_Huff_Body(&obj,file);
        fclose(file);
    } else{
        exit(-1);
    }
    DisplayHuffManStruct(&obj);
    return true;
}
#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_PROCESS_H

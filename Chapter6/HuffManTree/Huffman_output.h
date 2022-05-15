//
// Created by Zza on 2022/5/13.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_OUTPUT_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_OUTPUT_H

#include "./Huffman_disp.h"
#include <stdio.h>

// these funcs targeted at save res

/*
 * struct would at the top and then the linkers below.
 * after struct is the dynamic array
 * we must store the length of array in the struct
 *
 * for this specific huffman tree we get the basic info the file structure
 *
 * |file                    |
 * --------------------------
 * |struct of huffman       |
 * |                        |
 * |array of roots          |
 * |                        |
 * |struct of arr tree      |
 * |                        |
 * |node array              |
 * --------------------------
 *
 * */

bool Output_Huff_Body(HuffManTree* tar, FILE* file);
// in the huffman tree, we have two pointer member
// Bin_Tree_Arr is the tree pointer we assume using another func to store
// roots is an int array, we assume store beyond the struct, with length stored in elem_num
// after that, we call the tree body output func

bool Output_Tree_Body(Binary_Tree_Array* tar, FILE* file);
// this func is to output a tree
// is important that the of size of tree is 2*n+1
// however we store it in the struct of len

bool Input_Huff_Body(HuffManTree* tar, FILE* file);
// this func will read the tree with the rule set above

bool Input_Tree_Body(Binary_Tree_Array* tar, FILE* file);

//----------------------------------------------------------------------------------------------------------------------

// here we try to output result to file
bool Output_Encoding_Res(ResContainer* tar, FILE* file);

bool Input_Encoding_Res(ResContainer* tar, FILE* file);

//----------------------------------------------------------------------------------------------------------------------

// the huffman tree
bool Output_Huff_Body(HuffManTree* tar, FILE* file){
    fwrite(tar,sizeof(HuffManTree),1,file);
    fwrite(tar->roots, sizeof(int), tar->elem_num, file);
    Output_Tree_Body(tar->trees,file);
    return true;
}

bool Output_Tree_Body(Binary_Tree_Array* tar, FILE* file){
    fwrite(tar, sizeof(Binary_Tree_Array),1,file);
    fwrite(tar->elems, sizeof(bin_tree_arr_node),tar->len,file);
    return true;
}

bool Input_Huff_Body(HuffManTree* tar, FILE* file){
    fread(tar,sizeof(HuffManTree),1,file);
    tar->roots = malloc(sizeof(int)*tar->elem_num);
    fread(tar->roots, sizeof(int), tar->elem_num, file);
    tar->trees = malloc(sizeof(Binary_Tree_Array));
    Input_Tree_Body(tar->trees,file);
    return true;
}

bool Input_Tree_Body(Binary_Tree_Array* tar, FILE* file){
    fread(tar, sizeof(Binary_Tree_Array),1,file);
    tar->elems = malloc(sizeof(bin_tree_arr_node)*tar->len);
    fread(tar->elems,sizeof(bin_tree_arr_node),tar->len,file);
    return true;
}

//----------------------------------------------------------------------------------------------------------------------

bool Output_Encoding_Res(ResContainer* tar, FILE* file){
    for(int i=0; i < HUFFMAN_CODE_NUMS; i++){
        fwrite(tar->res[i],sizeof(char)*HUFFMAN_CODE_NUMS,1,file);
    }
    return true;
}

bool Input_Encoding_Res(ResContainer* tar, FILE* file){
    for(int i=0; i < HUFFMAN_CODE_NUMS; i++){
        tar->res[i] = malloc(sizeof(char)*HUFFMAN_CODE_NUMS);
        fread(tar->res[i],sizeof(char)*HUFFMAN_CODE_NUMS,1,file);
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_OUTPUT_H

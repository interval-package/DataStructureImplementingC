//
// Created by Zza on 2022/5/13.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_OUTPUT_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_OUTPUT_H

#include "./HuffManTree.h"

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


bool Huffman_Coding_Output();


bool Huffman_Coding_Input();


bool Output_Huff_Body();
// in the huffman tree, we have two pointer member
// Bin_Tree_Arr is the tree pointer we assume using another func to store
// roots is an int array, we assume store beyond the struct, with length stored in treeNums
// after that, we call the tree body output func

bool Output_Tree_Body();
// this func is to output a tree
// is important that the of size of tree is 2*n+1
// however we store it in the struct of len

bool Input_Huff_Body();


bool Input_Tree_Body();



//----------------------------------------------------------------------------------------------------------------------

// the huffman tree
bool Output_Huff_Body(){
    return true;
}

bool Output_Tree_Body(){
    return true;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_OUTPUT_H

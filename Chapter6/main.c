//
// Created by Zza on 2022/4/28.
//

//#include "HuffManTree/Huffman_output.h"
#include "HuffManTree/Huffman_wrapper.h"
//#include "Experiment/Traverse/Exp_Traverse.h"

#define BUFFER_LEN 2000

int main(){

    char* str = "HERE_IS_THE_EXAMPLE_STR_FOR_THE_HUFFMAN_TREE_ENCODING"
                "[THIS_FUNC_ONLY_READS_UPPER_CASE_WORDS_AND_SOME_OTHERS"
                "AND_NOT^"
                "[][][]\\[][]\\";

    Huff_Man_Generate_Write(str);

    Huff_Man_Generate_Read();

    return 0;
}

int main_(){
    char* str = "HERE_IS_THE_EXAMPLE_STR_FOR_THE_HUFFMAN_TREE_ENCODING"
                "[THIS_FUNC_ONLY_READS_UPPER_CASE_WORDS_AND_SOME_OTHERS"
                "AND_NOT^"
                "[][][]\\[][]\\";

    char buffer[BUFFER_LEN];
    buffer[BUFFER_LEN-1] = '\0';
    char res[BUFFER_LEN];
    res[BUFFER_LEN-1]='\0';

    pkg info;
    CalcCharFreq(str,&info);
    HuffManTree obj;
    Init_HuffMan(&obj,&info);
    HuffManEncoding(&obj);

    ResContainer container;
    HuffManDecode_Reverse(&obj, &container);
    DisplayContainer(&container);

    printf(str);
    printf("\n");

    Huff_Man_Replace(&container,str,buffer,BUFFER_LEN);
    printf(buffer);

    Huff_Rebuild(&obj,buffer,res,BUFFER_LEN);

    printf("\n");
    printf(res);

    ContainerDestruct(&container);
    HuffManDestruct(&obj);
    PkgDestruct(&info);
    return 0;
}
//
// Created by Zza on 2022/5/15.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_WRAPPER_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_WRAPPER_H

#define BUFFER_LEN 2000

#include "Huffman_output.h"
#include "Huffman_disp.h"
#include "Huffman_process.h"
#include "HuffManTreeEncoding.h"

bool Huff_Man_Replace(ResContainer* projection, const char* tar, char* buffer, int len){

    int iter = 0;
    int st;
    char* flag, *temp = buffer;
    while (iter < len && *tar){
//        这里必须要+1！
        st = (int) projection->res[*tar-HUFFMAN_CODE_BASE_CHAR][0];
        flag = &(projection->res[*tar-HUFFMAN_CODE_BASE_CHAR][st]);
        while (*flag){
//            printf("%c",*flag);
            *temp = *flag;
            temp++;
            flag++;
            iter++;
        }
        iter++;
        tar++;
    }

//    eof
    temp++;
    *temp = '\0';
    return true;
}

bool Huff_Rebuild(const HuffManTree * project, const char* tar, char* res, int res_len){
// here we'd use a tree to rebuild
// that the root id is the end id of the tree
// here we trance back, util get a leave
    int iter = 0;
    int cur = project->trees->len - 1;
    const int root = project->trees->len - 1;
    while (*tar && iter<res_len){
        cur = root;
        while (project->trees->elems[cur].left >= 0){
            if(*tar == '0'){
                cur = project->trees->elems[cur].left;
            } else{
                cur = project->trees->elems[cur].right;
            }
            tar++;
        }
        *res = project->trees->elems[cur].data.tar;
        res++;
        iter++;
    }
        *++res = '\0';
    return true;
};

int main_2(){

    char* str = "HERE_IS_THE_EXAMPLE_STR_FOR_THE_HUFFMAN_TREE_ENCODING"
                "[THIS_FUNC_ONLY_READS_UPPER_CASE_WORDS_AND_SOME_OTHERS"
                "AND_NOT^"
                "[][][]\\[][]\\";

    Huff_Man_Generate_Write(str);

    Huff_Man_Generate_Read();

    return 0;
}

int main_1(){
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

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_WRAPPER_H

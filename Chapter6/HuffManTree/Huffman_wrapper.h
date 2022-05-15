//
// Created by Zza on 2022/5/15.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_WRAPPER_H
#define DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_WRAPPER_H

#include "Huffman_output.h"
#include "Huffman_disp.h"
#include "Huffman_process.h"

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

#endif //DATASTRUCTUREIMPLEMENTINGC_HUFFMAN_WRAPPER_H

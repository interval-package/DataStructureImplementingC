//
// Created by Zza on 2022/3/29.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STRING_H
#define DATASTRUCTUREIMPLEMENTINGC_STRING_H

#include <stdlib.h>

#define DYNAMIC_STR_INIT_LEN 50
#define DYNAMIC_STR_INCREMENT 10

typedef struct String_sq_dyna{
    char *elems;
    int size;
    int len;
} str_sq, *pStr_sq;

pStr_sq String_sq_Get(){
    pStr_sq res = (pStr_sq) malloc(sizeof(str_sq));
    res->size = DYNAMIC_STR_INIT_LEN;
    res->len = 0;
    res->elems = (char*)malloc(sizeof(char)*DYNAMIC_STR_INIT_LEN);
    res->elems[0] = '\0';
    return res;
}

pStr_sq String_sq_Init(const char *tar){
    pStr_sq res = (pStr_sq) malloc(sizeof(str_sq));
    res->size = DYNAMIC_STR_INIT_LEN;
    int i = 0;
//    预留一个位置给0
    while(*tar && i < res->size - 1){
        res->elems[i] = *tar;
        tar++;
        i++;
    }
    res->elems[i+1] = '\0';
//    这里实际上是没有算上0的，+1是因为数组性质
    res->len = i + 1;
    return res;
}

void String_sq_Destruct(pStr_sq *p){
    free((*p)->elems);
    free(*p);
    *p = NULL;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_STRING_H

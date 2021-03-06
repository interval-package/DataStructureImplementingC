//
// Created by Zza on 2022/3/29.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STRING_H
#define DATASTRUCTUREIMPLEMENTINGC_STRING_H

#include <stdlib.h>
#include <stdbool.h>
#define DYNAMIC_STR_INIT_LEN 50
#define DYNAMIC_STR_INCREMENT 10

typedef struct String_sq_dyna{
    char *str;
    int size;
    int len;
} str_sq, *pStr;

pStr String_Get(){
    pStr res = (pStr) malloc(sizeof(str_sq));
    res->size = DYNAMIC_STR_INIT_LEN;
    res->len = 0;
    res->str = (char*)malloc(sizeof(char)*DYNAMIC_STR_INIT_LEN);
    res->str[0] = '\0';
    return res;
}

bool String_Construct(pStr res, const char *tar){
    return true;
}

pStr String_Init(const char *tar){
    pStr res = (pStr) malloc(sizeof(str_sq));
    res->size = DYNAMIC_STR_INIT_LEN;
    int i = 0;
//    预留一个位置给0
    while(*tar && i < res->size - 1){
        res->str[i] = *tar;
        tar++;
        i++;
    }
    res->str[i+1] = '\0';
//    这里实际上是没有算上0的，+1是因为数组性质
    res->len = i + 1;
    return res;
}

bool String_Destruct(pStr *p){
    free((*p)->str);
    free(*p);
    *p = NULL;
    return true;
}

bool String_Clear(pStr p){
    p->str[0] = '\0';
    p->len = 0;
    return true;
}

int String_Len_Certification(pStr p){
    char *temp= p->str;
    int i = 0;
    while (*temp){
        i++;
        temp++;
    }
    p->len = i;
    return i;
}

void String_Get_Sub(const pStr p, pStr res, int pos, int len){
    String_Clear(res);
    if(pos<0||pos+len>p->len||len>=res->size)return;
    int i=0;
    if(len>0){
        for(; i<len;i++){
            res->str[i] = p->str[pos+i];
        }
    } else{
        char *temp = &(p->str[pos]);
        while(*temp){
            res->str[i] = *temp;
            i++;
            temp++;
        }
    }
    res->len = i+1;
    res->str[i+1] = '\0';
}

void String_Copy_Static(pStr tar, pStr source){
    if(source->len>=tar->size)return;
    for(int i=0;i<=source->len;i++){
        tar->str[i] = source->str[i];
    }
}

void String_Copy_Dynamic(pStr tar, pStr source){
    if(source->len >= tar->size){
        tar->str = (char*)realloc(tar->str,sizeof(char)*(source->len+DYNAMIC_STR_INCREMENT));
    }
    for(int i=0;i<=source->len;i++){
        tar->str[i] = source->str[i];
    }
}

__attribute__((unused))
void String_Connect_Static(pStr p, pStr item){
//    size 里面包含了'\0'
    if(p->len+item->len>=p->size)return;
    int i=0;
    for(;i<=item->len;i++){
        p->str[p->len+i]=item->str[i];
    }
}

__attribute__((unused))
void String_Connect_Dynamic(pStr p, pStr item){
    if(item->len+p->len >= p->size){
        p->str = (char*)realloc(p->str,sizeof(char)*(item->len+p->len+DYNAMIC_STR_INCREMENT));
    }
    for(int i=0;i<=item->len;i++){
        p->str[p->len+i]=item->str[i];
    }
}

__attribute__((unused))
int String_Compare_Dict(pStr str_1, pStr str_2){
//    In the order of dictionary, finally the length
    char* p1 = str_1->str, *p2 = str_2->str;
    while(*p1 && *p2){
        if(*p1!=*p2)return *p1-*p2;
        p1++;p2++;
    }
    return str_1->len-str_2->len;
}




void String_Push(pStr source, char tar){
    source->len++;
    if(source->len == source->size){
        source->str = (char*)realloc(source->str,sizeof(char)*(source->size+DYNAMIC_STR_INCREMENT));
        source->size+=DYNAMIC_STR_INCREMENT;
    }
    source->str[source->len-1] = tar;
    source->str[source->len] = '\0';
}

#endif //DATASTRUCTUREIMPLEMENTINGC_STRING_H

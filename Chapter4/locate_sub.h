//
// Created by Zza on 2022/4/13.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_LOCATE_SUB_H
#define DATASTRUCTUREIMPLEMENTINGC_LOCATE_SUB_H

#include <stdlib.h>
#include "./String.h"

// Brute force
__attribute__((unused))
int String_Locate_Sub_Bf(pStr source, pStr tar){
    int pos = 0;
    char *p1_self, *p_tar;
    while(pos+tar->len<source->len){
        p_tar = tar->str;
        p1_self = &source->str[pos];
        while (*p_tar){
            if(*p_tar != *p1_self)
                break;
            p_tar++;
            p1_self++;
        };
        if(!*p_tar)return pos;
        pos++;
    };
    return pos;
}

// head-tail matching
// compare the first then last

// kmp method (knuth morris pratt)
// reuse the work, after a failure

void getNext(pStr p, int * next)
{
    next[0] = -1;
    int i = 0, j = -1;

    while (i < p->len)
    {
        if (j == -1 || p->str[i] == p->str[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

__attribute__((unused))
int KMP(pStr t, pStr p)
{
    int i = 0;
    int j = 0;

    int *next = (int*)malloc(sizeof(int)*(p->len+1));
    getNext(p,next);

    while (i < t->len && j < p->len)
    {
        if (j == -1 || t->str[i] == p->str[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }

    free(next);

    if (j == p->len)
        return i - j;
    else
        return -1;
}

// bm method

#endif //DATASTRUCTUREIMPLEMENTINGC_STRSTR_H

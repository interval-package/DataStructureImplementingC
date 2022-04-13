//
// Created by Zza on 2022/4/13.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STRSTR_H
#define DATASTRUCTUREIMPLEMENTINGC_STRSTR_H

#include <stdlib.h>
#include <string.h>

void getNext(char* p, int * next);

int strStr(const char * haystack, char * needle){
    int i = 0;
    int j = 0;
    int l = (int)strlen(needle);
//    strlen 非常关键的一个要点，就是这个返回的是double类型的数据
// 如果我们直接使用这个double与int进行比较的话，c语言没有强制转换，只有

    int *next = (int*)malloc(sizeof(int)*(strlen(needle)));
    getNext(needle,next);

    while (haystack[i] && j < l)
    {
        if (j == -1 || haystack[i] == needle[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }

    free(next);
    if (j >= strlen(needle))
        return i - j;
    else
        return -1;
}

void getNext(char* p, int * next)
{
    int i = 0, j = -1, len = (int)strlen(p);
    next[0] = -1;
    while (i < len)
    {
        if (j == -1 || p[i] == p[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

#endif //DATASTRUCTUREIMPLEMENTINGC_STRSTR_H

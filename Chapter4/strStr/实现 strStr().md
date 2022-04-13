# 实现 strStr()

[28. 实现 strStr()](https://leetcode-cn.com/problems/implement-strstr/)

实现 strStr() 函数。

给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。

## 说明：

- 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

- 对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与 C 语言的 strstr() 以及 Java 的 indexOf() 定义相符。




示例 1：

```
输入：haystack = "hello", needle = "ll"
输出：2
```

示例 2：

```
输入：haystack = "aaaaa", needle = "bba"
输出：-1
```

示例 3：

```
输入：haystack = "", needle = ""
输出：0
```

## 提示：

- 1 <= haystack.length, needle.length <= 104
- haystack 和 needle 仅由小写英文字符组成

## 算法：

使用KMP，KMP算法的详细分析放在另外的地方

## 题解：

```c
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
```
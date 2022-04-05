# KMP算法

## 算法优化

## 字符串的前缀和后缀

如果字符串A和B，存在A=BS，其中S是任意的非空字符串，那就称B为A的前缀。

例如，”Harry”的前缀包括{”H”, ”Ha”, ”Har”, ”Harr”}，我们把所有前缀组成的集合，称为字符串的前缀集合。

同样可以定义后缀A=SB， 其中S是任意的非空字符串，那就称B为A的后缀。

例如，”Potter”的后缀包括{”otter”, ”tter”, ”ter”, ”er”, ”r”}，然后把所有后缀组成的集合，称为字符串的后缀集合。要注意的是，字符串本身并不是自己的后缀。

## PMT表

**PMT中的值是字符串的前缀集合与后缀集合的交集中最长元素的长度**。

例如，对于”aba”，它的前缀集合为{”a”, ”ab”}，后缀 集合为{”ba”, ”a”}。两个集合的交集为{”a”}，那么长度最长的元素就是字符串”a”了，长 度为1，所以对于”aba”而言，它在PMT表中对应的值就是1。

再比如，对于字符串”ababa”，它的前缀集合为{”a”, ”ab”, ”aba”, ”abab”}，它的后缀集合为{”baba”, ”aba”, ”ba”, ”a”}， 两个集合的交集为{”a”, ”aba”}，其中最长的元素为”aba”，长度为3。

## Next数组

我们看到如果是在 j 位 失配，那么影响 j 指针回溯的位置的其实是第 j −1 位的 PMT 值，所以为了编程的方便， 我们不直接使用PMT数组，而是将PMT数组向后偏移一位。我们把新得到的这个数组称为next数组。

## Next求法

### 1.暴力



### 2.使用next[i-1]

```c
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
```

## Code

```c
__attribute__((unused))
int KMP(pStr t, pStr p)
{
    int i = 0;
    int j = 0;

    int *next = (int*)malloc(sizeof(int)*p->len);
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
```


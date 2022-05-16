# 设计实验：Huffman tree的实现

## 一、需求分析

对于多个字符，以及对应的频率，进行Huffman编码，使得该编码系统的空间效率最好。

### 基本需求

#### 1.初始化操作 Initialization

从终端字符集读入一个字符串，统计字符频率。按照权值以及字符，建立Huffman Tree，并且保存数据。

#### 2.编码 Encoding

利用已经建好的Huffman Tree对目标正文进行进行编码。保存编码结果数据。

#### 3.译码 Decoding

将上一步中使用Huffman Tree编码的结果，进行译码，保存数据。

#### 4.打印代码文件 Print

将编码结果以紧凑格式显示在终端。

将解解码结果显示在终端。

#### 5.打印树结构 Tree Printing

将已在内存中的Huffman Tree以最直观的形式显示在屏幕上，同时将此字符形式的Huffman Tree写入文件。

## 二、ADT设计

由于树的规模可以预知，所以我们使用静态树来进行存储。

为了方便回溯解码，我们使用了三叉链表的形式。

对于解码，我们实现了使用亲结点回溯的算法，以及使用栈的向下搜索算法。

## 三、使用说明

### 1.基本结构

#### encoding

对于Huffman树进行编码操作。对于一个Huffman树结构体，内部存储一个二叉树指针，以及一个根结点索引数组。

#### decoding

#### display

#### output&input

### 2.API接口

### 3.注意事项

## 四、调试结果

## 五、运行结果

为了方便映射，对于目标字符集只使用大写字符进行测试。

### 编码过程与解码过程

```c
int main(){

    char* str = "HERE_IS_THE_EXAMPLE_STR_FOR_THE_HUFFMAN_TREE_ENCODING"
                "[THIS_FUNC_ONLY_READS_UPPER_CASE_WORDS_AND_SOME_OTHERS"
                "AND_NOT^"
                "[][][]\\[][]\\";

    Huff_Man_Generate_Write(str);
    Huff_Man_Generate_Read();

    return 0;
}
```

测试结果：

```
id: 0   char: A freq: 6 left: -1        right: -1       parent: 47
id: 1   char: B freq: 0 left: -1        right: -1       parent: 31
id: 2   char: C freq: 3 left: -1        right: -1       parent: 42
id: 3   char: D freq: 5 left: -1        right: -1       parent: 46
id: 4   char: E freq: 14        left: -1        right: -1       parent: 55
id: 5   char: F freq: 4 left: -1        right: -1       parent: 45
id: 6   char: G freq: 1 left: -1        right: -1       parent: 38
id: 7   char: H freq: 6 left: -1        right: -1       parent: 49
id: 8   char: I freq: 3 left: -1        right: -1       parent: 43
id: 9   char: J freq: 0 left: -1        right: -1       parent: 35
id: 10  char: K freq: 0 left: -1        right: -1       parent: 34
id: 11  char: L freq: 2 left: -1        right: -1       parent: 40
id: 12  char: M freq: 3 left: -1        right: -1       parent: 44
id: 13  char: N freq: 8 left: -1        right: -1       parent: 51
id: 14  char: O freq: 7 left: -1        right: -1       parent: 50
id: 15  char: P freq: 3 left: -1        right: -1       parent: 43
id: 16  char: Q freq: 0 left: -1        right: -1       parent: 33
id: 17  char: R freq: 8 left: -1        right: -1       parent: 52
id: 18  char: S freq: 8 left: -1        right: -1       parent: 51
id: 19  char: T freq: 7 left: -1        right: -1       parent: 49
id: 20  char: U freq: 3 left: -1        right: -1       parent: 42
id: 21  char: V freq: 0 left: -1        right: -1       parent: 32
id: 22  char: W freq: 1 left: -1        right: -1       parent: 39
id: 23  char: X freq: 1 left: -1        right: -1       parent: 38
id: 24  char: Y freq: 1 left: -1        right: -1       parent: 37
id: 25  char: Z freq: 0 left: -1        right: -1       parent: 31
id: 26  char: [ freq: 6 left: -1        right: -1       parent: 47
id: 27  char: \ freq: 2 left: -1        right: -1       parent: 39
id: 28  char: ] freq: 5 left: -1        right: -1       parent: 45
id: 29  char: ^ freq: 1 left: -1        right: -1       parent: 36
id: 30  char: _ freq: 19        left: -1        right: -1       parent: 57
id: 31  char: s freq: 0 left: 1 right: 25       parent: 32
id: 32  char: s freq: 0 left: 31        right: 21       parent: 33
id: 33  char: s freq: 0 left: 32        right: 16       parent: 34
id: 34  char: s freq: 0 left: 33        right: 10       parent: 35
id: 35  char: s freq: 0 left: 34        right: 9        parent: 36
id: 36  char: s freq: 1 left: 35        right: 29       parent: 37
id: 37  char: s freq: 2 left: 36        right: 24       parent: 40
id: 38  char: s freq: 2 left: 6 right: 23       parent: 41
id: 39  char: s freq: 3 left: 22        right: 27       parent: 41
id: 40  char: s freq: 4 left: 37        right: 11       parent: 44
id: 41  char: s freq: 5 left: 38        right: 39       parent: 46
id: 42  char: s freq: 6 left: 2 right: 20       parent: 48
id: 43  char: s freq: 6 left: 8 right: 15       parent: 48
id: 44  char: s freq: 7 left: 12        right: 40       parent: 50
id: 45  char: s freq: 9 left: 5 right: 28       parent: 52
id: 46  char: s freq: 10        left: 3 right: 41       parent: 53
id: 47  char: s freq: 12        left: 0 right: 26       parent: 53
id: 48  char: s freq: 12        left: 42        right: 43       parent: 54
id: 49  char: s freq: 13        left: 7 right: 19       parent: 54
id: 50  char: s freq: 14        left: 44        right: 14       parent: 55
id: 51  char: s freq: 16        left: 13        right: 18       parent: 56
id: 52  char: s freq: 17        left: 17        right: 45       parent: 56
id: 53  char: s freq: 22        left: 46        right: 47       parent: 57
id: 54  char: s freq: 25        left: 48        right: 49       parent: 58
id: 55  char: s freq: 28        left: 4 right: 50       parent: 58
id: 56  char: s freq: 33        left: 51        right: 52       parent: 59
id: 57  char: s freq: 41        left: 30        right: 53       parent: 59
id: 58  char: s freq: 53        left: 54        right: 55       parent: 60
id: 59  char: s freq: 74        left: 56        right: 57       parent: 60
id: 60  char: s freq: 127       left: 58        right: 59       parent: 0
A: 11110
B: 0110100000000
C: 00000
D: 11100
E: 010
F: 10110
G: 1110100
H: 0010
I: 00010
J: 011010001
K: 0110100001
L: 011011
M: 01100
N: 1000
O: 0111
P: 00011
Q: 01101000001
R: 1010
S: 1001
T: 0011
U: 00001
V: 011010000001
W: 1110110
X: 1110101
Y: 0110101
Z: 0110100000001
[: 11111
\: 1110111
]: 10111
^: 01101001
_: 110

Process finished with exit code 0

```



## 六、源代码

## 七、总结


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

```c
/*
 * struct would at the top and then the linkers below.
 * after struct is the dynamic array
 * we must store the length of array in the struct
 *
 * for this specific huffman tree we get the basic info the file structure
 *
 * |file                    |
 * --------------------------
 * |struct of huffman       |
 * |                        |
 * |array of roots          |
 * |                        |
 * |struct of arr tree      |
 * |                        |
 * |node array              |
 * --------------------------
 *
 * */
```



### 2.API接口

#### 显示结构函数

#### 编码函数

#### 解码函数

#### 保存数据函数

```c
bool Output_Huff_Body(HuffManTree* tar, FILE* file);
// in the huffman tree, we have two pointer member
// Bin_Tree_Arr is the tree pointer we assume using another func to store
// roots is an int array, we assume store beyond the struct, with length stored in elem_num
// after that, we call the tree body output func

bool Output_Tree_Body(Binary_Tree_Array* tar, FILE* file);
// this func is to output a tree
// is important that the of size of tree is 2*n+1
// however we store it in the struct of len

bool Input_Huff_Body(HuffManTree* tar, FILE* file);
// this func will read the tree with the rule set above

bool Input_Tree_Body(Binary_Tree_Array* tar, FILE* file);

//----------------------------------------------------------------------------------------------------------------------

// here we try to output result to file
bool Output_Encoding_Res(ResContainer* tar, FILE* file);

bool Input_Encoding_Res(ResContainer* tar, FILE* file);

//----------------------------------------------------------------------------------------------------------------------
```

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

```

## 六、源代码

## 七、总结


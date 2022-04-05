//
// Created by 86189 on 2022/4/2.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_GENERAL_LIST_H
#define DATASTRUCTUREIMPLEMENTINGC_GENERAL_LIST_H

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

/*
 * 实际上广义表的数据结构的概念是很简单的
 * 对于广义表，只有头元素和尾元素两个结点
 * 头元素可以是原子也可以是一个表，尾元素一定要是一张表
 * */

typedef struct General_List_HeadRearMethod{
    char tag;
    union{
        ELEMENT_TYPE data;
        struct {
            struct General_List_HeadRearMethod* hp;
            struct General_List_HeadRearMethod* tp;
        }ptr;
    };

} GList_HR, *pGList_HR;

typedef struct General_List_SiblingMethod{
    char tag;
    union {
        ELEMENT_TYPE data;
        struct General_List_SiblingMethod *hp;
    };
    struct General_List_SiblingMethod* tp;

}GList_Sl, *pGList_Sl;





#endif //DATASTRUCTUREIMPLEMENTINGC_GENERAL_LIST_H

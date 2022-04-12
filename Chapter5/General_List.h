//
// Created by 86189 on 2022/4/2.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_GENERAL_LIST_H
#define DATASTRUCTUREIMPLEMENTINGC_GENERAL_LIST_H

#include <stdlib.h>

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

/*
 * 实际上广义表的数据结构的概念是很简单的
 * 对于广义表，只有头元素和尾元素两个结点
 * 头元素可以是原子也可以是一个表，尾元素一定要是一张表
 * */

#define ENUM_HR_DATA 'a'
#define ENUM_HR_PRT 'b'

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

#define ENUM_CS_CH '0'
#define ENUM_CS_CH_LESS '1'

typedef struct General_List_ChildSiblingMethod{
    char tag;
    union {
        ELEMENT_TYPE data;
        struct General_List_SiblingMethod *hp;
    };
    struct General_List_SiblingMethod* tp;

}GList_CS, *pGList_CS;

pGList_HR Get_GList_HR(){
    pGList_HR res = (pGList_HR)malloc(sizeof(GList_HR));
    res->tag = ENUM_HR_PRT;
    res->ptr.hp = NULL;
    res->ptr.hp = NULL;
    return res;
}

pGList_HR GetHead(pGList_HR obj){
    if(!(obj->ptr.hp))return NULL;
    return obj->data;
}

pGList_HR GetLen(pGList_HR *tar);

int GetDepth(pGList_HR *tar);

#endif //DATASTRUCTUREIMPLEMENTINGC_GENERAL_LIST_H

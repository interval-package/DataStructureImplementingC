//
// Created by 86189 on 2022/3/19.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_CITYMANAGEMENT_H
#define DATASTRUCTUREIMPLEMENTINGC_CITYMANAGEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_LEN 20
#define INFO_LEN 30

// 使用双向链表
typedef struct city{
//    设定的城市的cityId是必须要有的
    union {
        int cityId; // unique
        int len;
    };

    struct city *next, *before;
    char info[INFO_LEN];
    char name[NAME_LEN];
}city, *cityList;

cityList InitCityList(){
    cityList res = (cityList)malloc(sizeof(city));
    res->before = NULL;
    res->next = NULL;
    res->len = 0;
    strcpy(res->info,"no description");
    strcpy(res->name,"start of list");
    return res;
}

void DestructCity(cityList cl){
    cityList temp;
    while(cl){
        temp = cl->next;
        free(cl);
        cl = temp;
    }
}

void AddCity(cityList cl, const char* name, const char* info){
    cityList p = (cityList)malloc(sizeof(city));
//    city id 由我们分配,对于表为空,那么id设置为1
    strcpy(p->name,name);
    strcpy(p->info,info);
    p->cityId = cl->next?cl->next->cityId+1:1;
//    插入
    p->before = cl;
    p->next = cl->next;
    if(cl->next)cl->next->before = p;
    cl->next = p;
}

void DeleteCity_Id(cityList cl, int id){
    do{
        cl = cl->next;
    }
    while (cl && cl->cityId != id);
//    对于双链表的删除和插入
    if(cl){
        cl->before->next = cl->next;
        if(cl->next)cl->next->before = cl->before;
        free(cl);
    }
}

void DispCity(cityList c){
    printf("city id\t: %d\n"
           "city name\t: %s\n"
           "city info\t: %s\n",
           c->cityId,c->name,c->info
    );
}

void DispCity_All(cityList c){
    while (c->next){
        c = c->next;
        DispCity(c);
    }
}

int Comp_by_name(city* cl,city* tar){
    return strcmp(cl->name,tar->name);
}

int Comp_by_id(city* cl,city* tar){
    return cl->cityId == tar->cityId;
}

cityList FindCity(cityList cl, city *tar,int(*comp)(city*,city*)){
//    comp的结果是真为非0，假为0
//    返回的是结果的指针
    do{
        cl = cl->next;
    }while(cl && !comp(cl,tar));
//    没有找到就自然为NULL
    return cl;
}

void UpdateCity(cityList cl, int id, const char* name, const char* info){
    do{
        cl = cl->next;
    }
    while (cl && cl->cityId != id);
//    对于双链表的删除和插入
    if(cl){
        if(name)strcpy(cl->name,name);
        if(info)strcpy(cl->info,info);
    }
}

#endif //DATASTRUCTUREIMPLEMENTINGC_CITYMANAGEMENT_H

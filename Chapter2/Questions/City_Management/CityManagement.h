//
// Created by 86189 on 2022/3/19.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_CITYMANAGEMENT_H
#define DATASTRUCTUREIMPLEMENTINGC_CITYMANAGEMENT_H

#include <stdlib.h>
#include <stdio.h>

// 使用双向链表
typedef struct city{
//    设定的城市的cityId是必须要有的
    union {
        int cityId; // unique
        int len;
    };

    struct city *next, *before;
    char *info;
    char *name;
}city, *cityList;

cityList InitCityList(){
    cityList res = (cityList)malloc(sizeof(city));
    res->before = NULL;
    res->next = NULL;
    res->len = 0;
    return res;
}

void AddCity(cityList cl){
    cityList p = (cityList)malloc(sizeof(city));
//    city id 由我们分配,对于表为空,那么id设置为1
    p->cityId = cl->next?cl->next->cityId+1:1;
//    插入
    p->before = cl;
    p->next = cl->next;
    if(cl->next)cl->next->before = p;
    cl->next = p;
}

void DeleteCity(cityList cl, int id){
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
    while (c->next){
        c = c->next;
        printf("city id\t: %d\n"
               "city name\t: %s\n"
               "city info\t: %s\n",
               c->cityId,c->name,c->info
               );
    }
}

#endif //DATASTRUCTUREIMPLEMENTINGC_CITYMANAGEMENT_H

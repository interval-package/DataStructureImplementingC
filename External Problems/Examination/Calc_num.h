//
// Created by Zza on 2022/6/22.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_CALC_NUM_H
#define DATASTRUCTUREIMPLEMENTINGC_CALC_NUM_H

#include "stdbool.h"
#include "stdlib.h"

/*
 * this function is to calc the number of int in a str
 * */

#define INIT_SIZE 10
#define INCREMENT 10

typedef struct vector{
    int* body;
    int len;
    int size;
} vector, *vec_ptr;

bool vec_init(vec_ptr obj);

bool vec_destruct(vec_ptr);

void vec_pushback(vec_ptr obj, int tar);

void Clac_nums(char* tar){
    bool flag = false;
    int temp_num = 0;
    vector res;
    vec_init(&res);
    while (*tar){
        if(*tar > '0' && *tar < '9'){
            flag = true;
            temp_num *= 10;
            temp_num += *tar - '0';
        } else{
            if(flag){
                flag = false;
                vec_pushback(&res, temp_num);
                temp_num = 0;
            }
        }
        tar++;
    }
    vec_destruct(&res);
}

bool vec_init(vec_ptr obj){
    obj->body = (int*)malloc(INIT_SIZE*sizeof(int));
    obj->len = 0;
    obj->size = INIT_SIZE;
    return true;
}

bool vec_destruct(vec_ptr obj){
    free(obj->body);
    return true;
}

void vec_pushback(vec_ptr obj, int tar){
    if(obj->len == obj->size){
        obj->size+=INCREMENT;
        obj->body = realloc(obj->body,obj->size*sizeof(int));
    }
    obj->body[obj->len] = tar;
    obj->len++;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_CALC_NUM_H

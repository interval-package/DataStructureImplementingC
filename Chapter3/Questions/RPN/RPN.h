//
// Created by Zza on 2022/3/25.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_RPN_H
#define DATASTRUCTUREIMPLEMENTINGC_RPN_H

#define MAX_CAP 100

#include "../../Stack.h"

typedef struct RPN_Container{
    char operators[MAX_CAP];
    int top_operator;

    int operand[MAX_CAP];
    int top_operand;
}RPN;


void initRPN(RPN *obj){
    obj->top_operator = obj->top_operand = 0;
}

void PushOperator(RPN *obj, char tar){
    if(obj->top_operator==MAX_CAP)exit(-1);
    obj->operators[obj->top_operator++] = tar;
}

char PopOperator(RPN *obj){
    if(obj->top_operator){
        return obj->operators[--(obj->top_operator)];
    } else{
        return '\0';
    }
}

// suspect we get a notation like: 15 14 * 16 +


// the vars contain the notation we get
int ProcessOfRPN(RPN *obj, char* vars){
    char temp[MAX_CAP];
    int top = 0;
    while(*vars){
        switch (*vars) {
            case ' ':;
        }
        vars++;
    }
}

void RPNMain(){

}

#endif //DATASTRUCTUREIMPLEMENTINGC_RPN_H

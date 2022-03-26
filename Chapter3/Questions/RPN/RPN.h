//
// Created by Zza on 2022/3/25.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_RPN_H
#define DATASTRUCTUREIMPLEMENTINGC_RPN_H

#define MAX_CAP 100

#include <stdio.h>
#include "../../Stack.h"

typedef struct RPN_Container{
    char operators[MAX_CAP];
    int top_operator;

    int operand[MAX_CAP];
    int top_operand;
}RPN, *RPNp;


void initRPN(RPN *obj){
    obj->top_operator = obj->top_operand = 0;
}

void PushOperator(RPN *obj, char tar){
    if(obj->top_operator == MAX_CAP)exit(-1);
    obj->operators[obj->top_operator++] = tar;
}

char PopOperator(RPN *obj){
    if(obj->top_operator){
        return obj->operators[--(obj->top_operator)];
    } else{
        return '\0';
    }
}

char TopOperator(RPN *obj){
    return obj->operators[obj->top_operator-1];
}

void PushOperand(RPN *obj, int tar){
    if(obj->top_operand == MAX_CAP)exit(-1);
    obj->operand[obj->top_operand++] = tar;
}

int PopOperand(RPN *obj){
    if(obj->top_operand){
        return obj->operand[--(obj->top_operand)];
    } else{
        exit(0);
    }
}


//======================================================================================================================

// get the elem temp stack
int ArrayCap2Int(const int *arr, int top){
    int tar = 0;
    for(int i=0;i<top;i++){
        tar *= 10;
        tar += arr[i];
    }
    return tar;
}

// Calc Function of RPN
// suspect we get a notation like: 15 14 * 16 +
// the vars contain the notation we get
int CalcProcessOfRPN(const char *chars){
// 浮标指针
    char *vars = (char*)chars;
    sta obj = CreateStack(MAX_CAP);
//    寄存栈
    int temp[MAX_CAP];
    int a, b, top = 0;
    while(*vars){
//        读入数字，到临时存储栈中
        if(*vars >= '0' && *vars <= '9'){
            temp[top++] = *vars - '0';
            vars++;
            continue;
        }
        if(*vars == ' '){
//            遇到空格并且寄存栈内有东西，则将寄存栈内的对象转化为int，存到操作数中
            if(top){
                PushBack(obj, ArrayCap2Int(temp,top));
                top = 0;
            }
            vars++;
            continue;
        }
//        到这里我们就认为是遇到了操作符了
        a = Pop(obj);
        b = Pop(obj);

        switch (*vars) {
            case '*':
                PushBack(obj,a*b);
                break;
            case '+':
                PushBack(obj,a+b);
                break;
            case '-':
                PushBack(obj,a-b);
                break;
            case '/':
                PushBack(obj,a/b);
                break;
        }
        vars++;
    }
    top = Pop(obj);
    DestroyStack(obj);
    return top;
}

void RPNMain(){
    char obj[] = "14 15 + 3 *";
    printf("%d",CalcProcessOfRPN(obj));
}

//======================================================================================================================
#endif //DATASTRUCTUREIMPLEMENTINGC_RPN_H

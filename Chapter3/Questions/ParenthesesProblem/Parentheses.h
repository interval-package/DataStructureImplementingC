//
// Created by Zza on 2022/3/27.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_PARENTHESES_H
#define DATASTRUCTUREIMPLEMENTINGC_PARENTHESES_H

#ifndef ELEM
#define ELEM
typedef char ELEMENT_TYPE;
#endif

#include "../../Stack.h"

int JudgeParentheses(char *tars){
// tars should be a valid phrase, end with '\0'
// len is the capacity of stack
    sta container = CreateStack(10);
    PushBack(container,'#');
    ELEMENT_TYPE temp;
    while(*tars){
//    phase 1
        switch (*tars) {
            case '(':;
            case '[':;
            case '{': {
                PushBack(container, *tars);
                break;
            }
            case ')':;
            case ']':;
            case '}':{
                temp = Pop(container);
                if(*tars-2==temp){
                    break;
                } else{
                    DestroyStack(container);
                    return 0;
                }
            }
        }
        tars++;
    }
    DestroyStack(container);
    return 1;
}


#endif //DATASTRUCTUREIMPLEMENTINGC_PARENTHESES_H

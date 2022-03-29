//
// Created by Zza on 2022/3/29.
//

/*
 * Hanoi tower is a good example of recursion stack
 * with three process save the condition in stack and trace back
 * */

#ifndef DATASTRUCTUREIMPLEMENTINGC_HANOITOWER_H
#define DATASTRUCTUREIMPLEMENTINGC_HANOITOWER_H

#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

#include "../../Stack.h"

int move(char,int,char);

int hanoi(int n,char x,char y,char z)
{
    if(n==1)
        move(x,1,z);
    else
    {
        hanoi(n-1,x,z,y);
        move(x,n,z);
        hanoi(n-1,y,x,z);
    }
    return 0;
}

int move(char getone,int n,char putone)
{
    static int k=1;
    printf("%2d:%3d # %c---%c\n",k,n,getone,putone);
    if(k++%3==0)
        printf("\n");
    return 0;
}

#endif //DATASTRUCTUREIMPLEMENTINGC_HANOITOWER_H

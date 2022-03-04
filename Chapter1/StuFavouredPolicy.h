//
// Created by 86189 on 2022/2/26.
//
// student favoured policy
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_STUFAVOUREDPOLICY_H
#define DATASTRUCTUREIMPLEMENTINGC_STUFAVOUREDPOLICY_H
#include <stdlib.h>
#include <math.h>
#include <time.h>

// define the const of this project
#define GENERAL_FEE 1000
#define MAX_STU_LEN 20

// implement macro func
#define FAVOUR_POLICY_PTR(sp) (sp)->Fee*=(((sp)->Score)>=85?0.85:1.00);

// define the student
typedef struct student{
    int Score;
    int Fee;
} stu;


// 初始化操作，使用统一的学费
void stuInit_General(stu* sp, int score){
    sp->Score=score;
    sp->Fee=GENERAL_FEE;
}

// 初始化
void stuInit(stu* sp, int score, int Fee){  // c没有直接的重载
    sp->Score=score;
    sp->Fee=Fee;
}


// 对数组进行初始化操作
void groupInit(stu sAr[], int len){
    for(int i=0; i < len; i++, sAr++){
//        对学生进行初始化
        stuInit(sAr,rand()%150-25,rand()%1000-200);
    }
}


// 对数组类型进行学生优惠政策判断，并且打印输出
void StuFavoredPolicyCertification(stu sArIn[],int len){
    for(int i=0; i < len; i++, sArIn++){
        if(sArIn->Score >= 0 && sArIn->Score <= 100 && sArIn->Fee>0){
            printf("input valid,stu:%d score:%d\nFee Before:%d;",i,sArIn->Score,sArIn->Fee);
            FAVOUR_POLICY_PTR(sArIn)
            printf(" Fee After:%d\n",sArIn->Fee);
        }
        else{
//            如果为输出异常值，则打印判断失败
            printf("invalid input,stu:%d falied with Score:%d Fee:%d\n",i,sArIn->Score,sArIn->Fee);
        }
    }
}


#endif //DATASTRUCTUREIMPLEMENTINGC_STUFAVOUREDPOLICY_H

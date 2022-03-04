#include <stdio.h>
#include "Chapter1/StuFavouredPolicy.h"

int main(){
    stu stuArr[MAX_STU_LEN];
    groupInit(stuArr,MAX_STU_LEN);
    StuFavoredPolicyCertification(stuArr,MAX_STU_LEN);
    return 0;
}

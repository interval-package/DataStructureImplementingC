//
// Created by Zza on 2022/4/11.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_TREE_CHILD_SIBLING_H
#define DATASTRUCTUREIMPLEMENTINGC_TREE_CHILD_SIBLING_H

#include <stdlib.h>
#include <errno.h>
#ifndef ELEM
#define ELEM
typedef int ELEMENT_TYPE;
#endif

typedef struct Tree_Child_Sibling{
    ELEMENT_TYPE data;
    struct Tree_Child_Sibling *parent, *prev, *post, *first_child;
} Tree_CS, *CSTree_Node;

#endif //DATASTRUCTUREIMPLEMENTINGC_TREE_CHILD_SIBLING_H

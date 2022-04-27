cmake_minimum_required(VERSION 3.20)
project(DataStructureImplementingC C)

set(CMAKE_C_STANDARD 99)

add_executable(
# main
        DataStructureImplementingC

        main.c
        init.c

        "Mid Term Examination/MidTermQues.h"

# External Problems
        "External Problems/UnDone/findMedianSortedArrays.h"
        "External Problems/UnDone/IsMatch_RegulaExpression.h"
        "External Problems/SelfDivide/SelfDivideNumbers.h"
        "External Problems/CanReorderDoubled/CanReorderedDoubled.h"
        "External Problems/RomanToInt/RomanToInt.h"
        "External Problems/Os/SleepingBarber/Sleeping_Barber.h"
        "External Problems/Os/IPC/IPC.h"
        "External Problems/Os/HRRF/HRRF.h"
        "External Problems/Os/BankerResourceDispatch/BankerResourceDispatch.h"

# chapter 1
#        Chapter1/StuFavouredPolicy.h

# chapter 2
        Chapter2/Sequential_List.h
        Chapter2/LinkedList.h Chapter2/StaticLinkedList.h
        Chapter2/DoublyLinkedList.h
        Chapter2/Questions/SortByAccessFrequency/SortByAccessFrequency.h
        Chapter2/Circular_Linked_List.h
        "Chapter2/Questions/Josephus problem/JosephusProblem.h"
        Chapter2/Questions/City_Management/CityManagement.h

# chapter 3
        Chapter3/Stack.h Chapter3/Queue.h
        Chapter3/Questions/RPN/RPN.h Chapter3/TwinStack.h
        Chapter3/Questions/ParenthesesProblem/Parentheses.h
        Chapter3/QueueImitationByStack.h
        Chapter3/Questions/HanoiTower/HanoiTower.h
        Chapter3/Questions/TrainTrans/TrainTrans.h

        "Chapter3/Experiments/ParkingLot Management/ParkingLot_Management.h"
        "Chapter3/Experiments/Product ManageMent/Product_Management.h"

# chapter 4
        Chapter4/String.h
        Chapter4/locate_sub.h
        Chapter4/strStr/strStr.h

# chapter 5
        Chapter5/General_List.h
        Chapter5/Sparse_Matrix.h
        "Chapter5/Orthogonal sparse matrix.h"

# chapter 6
        "Chapter6/Binary Tree/BinaryTree_Link.h"
        Chapter6/Tree_Child_Sibling.h
        "Chapter6/Binary Tree/BinaryTree_Array.h"
        "Chapter6/Binary Tree/BinTreeTraverse/ques/PreOrderTraverse.h"
        "Chapter6/AVL Tree/IsAVL.h"
        "Chapter6/Binary Tree/BinTreeTraverse/BinTreeTraverse.h"
        "Chapter6/Binary Tree/BinTreeTraverse/LevelTraverse.h"
        "Chapter6/Binary Tree/TreeUtils/BinTreeUtils.h"
        "Chapter6/Binary Tree/BinTree_Thread.h"

        Chapter6/HuffManTree/HuffManTreeEncoding.h
        Chapter6/HuffManTree/HuffManTreeDecoding.h
        Chapter6/HuffManTree/HuffManTree.h
        "Chapter6/Binary Tree/Rebuild_BinTree/TreeRebuild.h"
        "Chapter6/Binary Tree/TreeUtils/ModifyTreeLeaves.h")

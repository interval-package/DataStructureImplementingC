cmake_minimum_required(VERSION 3.20)
project(DataStructureImplementingC C)

set(CMAKE_C_STANDARD 11)

# chapter 1
#        Chapter1/StuFavouredPolicy.h

add_executable(
# main
        DataStructure_Implementing_C

        main.c
        init.c

        "Mid Term Examination/MidTermQues.h"
)

add_executable(
        Chapter2-3
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

        Chapter3/main.c
        Chapter7/GraphTraverse/BFS.h Chapter7/GraphTraverse/DFS.h
        Chapter7/MinimumCostSpanningTree/PrimAlgorithm.h Chapter7/MinimumCostSpanningTree/KruskalAlgorithm.h Chapter7/MinimumLenthPath/DijkstraAlgorithm.h Chapter7/MinimumLenthPath/FolydAlgorithm.h)

add_executable(
        Chapter4-5
# chapter 4
        Chapter4/String.h
        Chapter4/locate_sub.h
        Chapter4/strStr/strStr.h

# chapter 5
        Chapter5/General_List.h
        Chapter5/Sparse_Matrix.h
        "Chapter5/Orthogonal sparse matrix.h"

        Chapter5/main.c
)

add_executable(
        External_Problems

        # External Problems
        "External Problems/UnDone/findMedianSortedArrays.h"
        "External Problems/UnDone/IsMatch_RegulaExpression.h"
        "External Problems/SelfDivide/SelfDivideNumbers.h"
        "External Problems/CanReorderDoubled/CanReorderedDoubled.h"
        "External Problems/RomanToInt/RomanToInt.h"
        "Os/SleepingBarber/Sleeping_Barber.h"
        "Os/IPC/IPC.h"
        "Os/HRRF/HRRF.h"
        "Os/BankerResourceDispatch/BankerResourceDispatch.h"
        "External Problems/main.c"
)

add_executable(
        Chapter6

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
        "Chapter6/Binary Tree/TreeUtils/ModifyTreeLeaves.h"
        Chapter6/main.c
)

add_executable(
        Chapter7

        Chapter7/main.c
        Chapter7/Graph.h
)



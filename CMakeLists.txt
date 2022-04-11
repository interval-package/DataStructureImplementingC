cmake_minimum_required(VERSION 3.20)
project(DataStructureImplementingC C)

set(CMAKE_C_STANDARD 99)

add_executable(
# main
        DataStructureImplementingC main.c

# chapter 1
#        Chapter1/StuFavouredPolicy.h

# chapter 2
        Chapter2/Sequential_List.h
        Chapter2/LinkedList.h Chapter2/StaticLinkedList.h Chapter2/DoublylinkedList.h
#        Chapter2/Questions/SortByAccessFrequency/SortByAccessFrequency.h
#        Chapter2/Questions/SortByAccessFrequency/SortByAccessFrequency.c
        Chapter2/Circular_Linked_List.h
#        "Chapter2/Questions/Josephus problem/JosephusProblem.h"
#        Chapter2/Questions/City_Management/CityManagement.h

# chapter 3
        Chapter3/Stack.h Chapter3/Queue.h
#        Chapter3/Questions/RPN/RPN.h Chapter3/TwinStack.h
#        Chapter3/Questions/ParenthesesProblem/Parentheses.h
        Chapter3/QueueImitationByStack.h
#        Chapter3/Questions/HanoiTower/HanoiTower.h
        Chapter3/Questions/TrainTrans/TrainTrans.h

# chapter 4
        Chapter4/String.h

# chapter 5
        Chapter5/General_List.h
        Chapter5/Sparse_Matrix.h

# External Problems
#        "External Problems/findMedianSortedArrays.h"
#        "External Problems/IsMatch_RegulaExpression.h"
#        "External Problems/SelfDivideNumbers.h"
#        "External Problems/CanReorderDoubled/CanReorderedDoubled.h"
#        "External Problems/RomanToInt/RomanToInt.h"
#        "External Problems/SleepingBarber/Sleeping_Barber.h"

        "Chapter5/Orthogonal sparse matrix.h"

        Chapter6/BinaryTree.h Chapter6/Tree_Seq.h Chapter6/Tree_Child_Sibling.h)

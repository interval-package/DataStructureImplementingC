cmake_minimum_required(VERSION 3.20)
project(DataStructureImplementingC C)

set(CMAKE_C_STANDARD 99)

add_executable(
        DataStructureImplementingC main.c

        Chapter1/StuFavouredPolicy.h

        Chapter2/Sequential_List.h
        Chapter2/LinkedList.h Chapter2/StaticLinkedList.h Chapter2/DoublylinkedList.h
        Chapter2/Questions/SortByAccessFrequency/SortByAccessFrequency.h
        Chapter2/Questions/SortByAccessFrequency/SortByAccessFrequency.c
        Chapter2/Circular_Linked_List.h
        "Chapter2/Questions/Josephus problem/JosephusProblem.h"
        Chapter2/Questions/City_Management/CityManagement.h
        Chapter3/Stack.h )

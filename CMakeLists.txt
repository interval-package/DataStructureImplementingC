cmake_minimum_required(VERSION 3.20)
project(DataStructureImplementingC C)

set(CMAKE_C_STANDARD 99)

add_executable(
        DataStructureImplementingC main.c

        Chapter1/StuFavouredPolicy.h

        Chapter2/Sequential_List.h
        Chapter2/LinkedList.h Chapter2/StaticLinkedList.h Chapter2/DoublylinkedList.h
        Chapter2/Questions/SortByAccessFrequency/SortByAccessFrequency.h Chapter2/Questions/SortByAccessFrequency/SortByAccessFrequency.c


        Chapter3/Stack.h Chapter2/Cricular_Linked_List.h "Chapter2/Questions/Josephs problem/JosephsProblem.h" Chapter2/Questions/CityManagement/CityManageMent.h)

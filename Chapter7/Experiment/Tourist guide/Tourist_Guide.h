//
// Created by Zza on 2022/5/17.
//

#ifndef DATASTRUCTUREIMPLEMENTINGC_TOURIST_GUIDE_H
#define DATASTRUCTUREIMPLEMENTINGC_TOURIST_GUIDE_H

#include "../../Graph.h"
#include "../../MinimumLengthPath/FloydAlgorithm.h"
#include "../../MinimumLengthPath/Hamiltonian_Algorithm.h"
#include "../Traveling Salesman Problem/TSP.h"

//======================================================================================================================
// interface functions

void Tourist_guide_interface();

void Tourist_guide_actions();

void Tourist_show_map();

//======================================================================================================================
// kernel functions

// get the min path, using the floyd

// Traveling salesman problem



//======================================================================================================================
//tourist guide main

#define VEX_NUM 5

void touring(){
    int init_data[VEX_NUM][VEX_NUM] = {
            {INF,3,INF,8,9},
            {3,INF,3,10,5},
            {INF,3,INF,4,3},
            {8,3,INF,4,3},
            {9,5,3,20,INF}
    };

}

//======================================================================================================================


//======================================================================================================================


#endif //DATASTRUCTUREIMPLEMENTINGC_TOURIST_GUIDE_H

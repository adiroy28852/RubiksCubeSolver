#include<bits/stdc++.h>
#include "../model/Rubikscube.h"
#include "DFSsolver.h"

#ifndef RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H

template <typename T, typename H>
class IDDFSsolver{
    private:
    int maxDepth;
    vector<Rubikscube::MOVE> moves;

    public:
    T rubiksCube;
    
    IDDFSsolver(T _rubiksCube, int _maxDepth = 7){
        rubiksCube= _rubiksCube;
        maxDepth= _maxDepth;
    }

    vector<Rubikscube::MOVE> solver(){
        for(int i=1; i<=maxDepth; i++){
            DFSsolver<T, H> dfssolver(rubiksCube, i);
            moves = dfssolver.solve();
            if(dfdssolver.rubiksCube.isSolved()){
                rubiksCube = dfssolver.rubiksCube;
                break;
            }
        }
        return moves;
    }
}

#endif
#include <vector>
#include "../model/Rubikscube.h"

#ifndef RUBIKS_CUBE_SOLVER_DFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_DFSSOLVER_H

template <typename T, typename H>
class DFSsolver{
    private:
    vector<Rubikscube::MOVE> moves;
    int maxDepth;

    bool dfs(int depth){
        if(rubiksCube.isSolved())return 1;
        if(depth >= maxDepth)return 0;
        for(int i=0; i<18; i++){
            if(!moves.empty() && i / 3 == static_cast<int>(moves.back()) / 3) continue;
            rubiksCube.move(Rubikscube::MOVE(i));
            moves.push_back(Rubikscube::MOVE(i));
            if(dfs(depth+1))return 1;
            moves.pop_back();
            rubiksCube.invert(Rubikscube::MOVE(i));
        }
        return 0;
    }


    public:
    T rubiksCube;

    DFSsolver(T _rubiksCube, int _maxDepth=8){
        rubiksCube= _rubiksCube;
        maxDepth= _maxDepth;
    }
    vector<Rubikscube::MOVE> solve(){
        moves.clear();
        dfs(0);
        return moves;
    }
};

#endif

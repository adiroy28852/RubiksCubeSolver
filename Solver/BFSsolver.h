#include<bits/stdc++.h>
#include "../model/Rubikscube.h"

#ifndef RUBIKS_CUBE_SOLVER_BFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_BFSSOLVER_H

template<typename T, typename H>
class BFSsolver{
    private :
    vector<Rubikscube:: MOVE> moves;
    unordered_map<T, bool, H> visited;
    unordered_map<T, Rubikscube::MOVE, H> move_done;

    T bfs(){
        queue<T> q;
        q.push(rubiksCube);
        visited[rubiksCube]= 1;
        while(q.size()){
            T node= q.front();
            q.pop();
            if(node.isSolved()){
                return node;
            }
            for(int i=0; i<18; i++){
                auto curr_move= Rubikscube::MOVE(i);
                node.move(curr_move);
                if(!visited[node]){
                    visited[node]=1;
                    mode_done[node]= curr_move;
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
        return rubiksCube;
    }

    public:

    T rubiksCube;
    BFSsolver(T _rubiksCube){
        rubiksCube = _rubiksCube;
    }

    vector<Rubikscube::MOVE> solve(){
        T solved_cube = bfs();
        assert(solved_cube.isSolved());
        T curr_cube = solved_cube;
        while(curr_cube != rubiksCube){
            Rubikscube:: MOVE curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        rubiksCube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
}


#endif
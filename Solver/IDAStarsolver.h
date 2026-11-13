#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include "../model/Rubikscube.h"

#include "../PatternDatabases/CornerPatternDB.h"
#ifndef RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H

template <typename T, typename H>
class IDAStarsolver{
    private:
    CornerPatternDB cornerDB;
    vector<Rubikscube::MOVE> moves;
    unordered_map<T, Rubikscube::MOVE, H> move_done;
    unordered_map<T, bool, H> visited;

    struct Node{
        T cube;
        int depth;
        int estimate;

        Node(T _cube, int _depth, int _estimate) : cube(_cube), depth(_depth), estimate(_estimate){};

    };

    struct compareCube{
        bool operator() (pair <Node, int> const &p1, pair<Node, int> const &p2){
            auto n1= p1.first, n2= p2.first;
            if(n1.depth + n1.estimate == n2.depth + n2.estimate){
                return n1.estimate > n2.estimate;
            }
            else return n1.depth + n1.estimate > n2.depth + n2.estimate;
        }
    };

    void resetStructure(){
        moves.clear();
        move_done.clear();
        visited.clear();
    }

    pair<T, int> IDAstar(int bound){
        priority_queue<pair<Node, int>, vector<pair<Node, int>>, compareCube> pq;
        Node start= Node(rubikscube, 0, cornerDB.getNumMoves(rubikscube));
        pq.push({start, 0});
        int nextbound= numeric_limits<int>::max();
        while(pq.size()){
            auto p= pq.top();
            pq.pop();
            Node node= p.first;

            if(visited[node.cube])continue;

            visited[node.cube]= 1;
            move_done[node.cube] = Rubikscube::MOVE(p.second);
            if(node.cube.isSolved())return {node.cube, bound};
            node.depth++;
            for(int i=0; i<18; i++){
                auto curr_move = Rubikscube::MOVE(i);
                node.cube.move(curr_move);
                if(!visited[node.cube]){
                    node.estimate = cornerDB.getNumMoves(node.cube);
                    if(node.estimate + node.depth > bound){
                        nextbound = min(nextbound , node.estimate + node.depth);
                    }
                    else {
                        pq.push({node, i});
                    }
                }
                node.cube.invert(curr_move);
            }
        }
        return {rubikscube, nextbound};
    }

    public:
    
    T rubikscube;

    IDAStarsolver(T _rubikscube, string fileName){
        rubikscube = _rubikscube;
        if(!cornerDB.fromFile(fileName)) throw runtime_error("Failed to open corner pattern database: " + fileName);
    }

    vector<Rubikscube::MOVE> solve() {
        moves.clear();
        move_done.clear();
        visited.clear();
        int bound = cornerDB.getNumMoves(rubikscube);
        auto p = IDAstar(bound);
        while(p.second != bound && p.second != numeric_limits<int>::max()){
            resetStructure();
            bound = p.second;
            p= IDAstar(bound);
        }
        if(p.second == numeric_limits<int>::max()){
            throw runtime_error("IDA* could not find a solution with the loaded pattern database");
        }

        T solved_cube = p.first;
        assert(solved_cube.isSolved());
        T curr_cube = solved_cube;

        while(!(curr_cube == rubikscube)){
            Rubikscube ::MOVE curr_move = move_done.at(curr_cube);
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        rubikscube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif

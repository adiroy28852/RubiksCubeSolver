#include "CornerDBmaker.h"
#include "../model/RubikscubeBitboard.cpp"

using namespace std;

CornerDBMaker:: CornerDBMaker(string _filename): fileName(_filename), cornerDB(9) {}

CornerDBMaker :: CornerDBMaker(string _filename, uint8_t init_val)
    : fileName(_filename), cornerDB(init_val) {}

bool CornerDBMaker ::bfsAndStore() {
    RubikscubeBitboard cube;
    queue<RubikscubeBitboard> q;
    q.push(cube);
    int curdepth=0;
    cornerDB.setNumMoves(cube, 0);
    while(q.size()){
        int n= q.size();
        curdepth++;
        if(curdepth==9)break;
        for(int i=0; i<n; i++){
            RubikscubeBitboard node= q.front();
            q.pop();
            for(int i=0; i<18; i++){
                auto curr_move= Rubikscube::MOVE(i);
                node.move(curr_move);
                if((int)cornerDB.getNumMoves(node)>curdepth){
                    if(cornerDB.setNumMoves(node, curdepth)) q.push(node);
                }
                node.invert(curr_move);
            }
        }
    }
    cornerDB.toFile(fileName);
    return 1;
}

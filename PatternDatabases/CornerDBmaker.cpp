#include "CornerDBmaker.h"

using namespace std;

CornerDBMaker:: CornerDBMaker(string _filename){
    filename= _filename;
}

CornerDBMaker :: CornerDBMaker(string _filename, uint8_t init_val){
    fileName = _filename;
    cornerDB = CornerPatternDB(init_val);
}

bool CornerDbMaker ::bfsAndStore() {
    RubikscubeBitboard cube;
    queue<RubikscubeBitboard> q;
    q.push(cube);
    int curdepth=0;
    cornerDB.setNumMoves(cube, 0);
    while(q.size()){
        int n= q.size();
        curdepth++;
        if(curdepth==0)break;
        for(int i=0; i<n; i++){
            RubikscubeBitboard node= q.front();
            q.pop();
            for(int i=0; i<18; i++){
                auto curr_movve= Rubikscube::MOVE(i);
                node.move(curr_move);
                if((int)cornerDB.getNumMoves(node)>curdepth){
                    cornerDB.setNumMoves(node, curdepth);
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
    }
    cornderDB.toFile(fileName);
    return 1;
}
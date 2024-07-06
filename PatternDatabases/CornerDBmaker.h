#ifndef RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H
#define RUBIKS_CUBE_SOLVER_CORNERDBMAKER_H

#include <CornerPatternDB.h>
#include "../model/RubikscubeBitboard.cpp"

using namespace std;
class CornerDBMaker{
    private:
    string fileName;
    CornerPatternDB cornerDB;

    public:
    CornerDBMaker(string _filename);
    CornerDBMaker(string _filename, uint8_t init_val);

    bool bfsAndStore();
}

#endif
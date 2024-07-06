#ifndef RUBIKS_CUBE_SOLVER_CORNERPATTERNDB_H
#define RUBIKS_CUBE_SOLVER_CORNERPATTERNDB_H

#include "../Model/Rubikscube.h"
#include "./Patterndatabase.h"
#include "./Permutationindexer.h"

using namespace std;

class CornerPatternDB : public Patterndatabase{
    
    typedef Rubikscube::FACE F;

    Permutationindexer(8) permidxr;

    public:

    CornerPatternDB();
    CornerPatternDB(uint8_t init_val);
    uint32_t getDatabaseindex(const Rubikscube cube) const;
}

#endif 
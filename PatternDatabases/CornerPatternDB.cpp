#include "CornerPatternDB.h"

CornerPatternDB :: CornerPatternDB(): PatternDatabase(100179840) {}

CornerPatternDB :: CornerPatternDB(uint8_t init_val) : Patterndatabase(100179840, init_val){}

uint32_t CornerPatternDB :: getDatabaseindex (const Rubikscube &cube) const{
    array<uint8_t, 8> cornerPerm = {
        cube.getCornerIndex(0),
        cube.getCornerIndex(1),
        cube.getCornerIndex(2),
        cube.getCornerIndex(3),
        cube.getCornerIndex(4),
        cube.getCornerIndex(5),
        cube.getCornerIndex(6),
        cube.getCornerIndex(7),
    };

    uint32_t rank = this->permidxr.rank(cornerPerm);

    array<uint8_t, 7> cornerOrientation = {
        cube. getCornerOrientation(0), 
        cube. getCornerOrientation(1), 
        cube. getCornerOrientation(2), 
        cube. getCornerOrientation(3), 
        cube. getCornerOrientation(4), 
        cube. getCornerOrientation(5), 
        cube. getCornerOrientation(6), 
    };

    uint32_t orientationNum = ( cornerOrientation[0] * 729 + cornerOrientation[1] * 243 + 
                                cornerOrientation[2] * 81 + cornerOrientation[3] * 27 +
                                cornerOrientation[4] * 9 + cornerOrientation[5] * 3 + 
                                cornerOrientation[6]);

    return (rank*2187) _ orientationNum;
}
#ifndef RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H

#include "../model/Rubikscube.h"
#include "Nibblearray.h"
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class Patterndatabase{
    
    Nibblearray database;
    size_t size;
    size_t numItems;
    uint8_t initValue;

    Patterndatabase() = delete;

    public:

    Patterndatabase(const size_t size);

    Patterndatabase(const size_t size, uint8_t init_val);

    virtual uint32_t getDatabaseindex(const Rubikscube &cube) const = 0;

    virtual bool setNumMoves(const Rubikscube &cube, const uint8_t numMoves);

    virtual bool setNumMoves(const uint32_t ind, const uint8_t numMoves);

    virtual uint8_t getNumMoves(const Rubikscube &cube)const;

    virtual uint8_t getNumMoves(const uint32_t ind)const;

    virtual size_t getSize() const;

    virtual size_t getNumItems() const;
    
    virtual bool isFull() const;

    virtual void toFile(const string &filePath)const;

    virtual bool fromFile(const string &filePath);

    virtual vector<uint8_t> inflate() const;

    virtual void reset();
};

#endif

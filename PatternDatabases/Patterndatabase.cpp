#include "Patterndatabase.h"
#include <fstream>
#include <stdexcept>
using namespace std;

Patterndatabase::Patterndatabase(const size_t size):
    database(size, 0xFF), size(size), numItems(0), initValue(0x0F){
}

Patterndatabase::Patterndatabase(const size_t size, uint8_t init_val):
    database(size, init_val), size(size), numItems(0), initValue(init_val & 0x0F){
}

bool Patterndatabase::setNumMoves(const uint32_t ind, const uint8_t numMoves){
    uint8_t oldMoves = this->getNumMoves(ind);

    if(oldMoves >numMoves){
        if(oldMoves == this->initValue) this->numItems++;
        this->database.set(ind, numMoves);
        return 1;
    }
    return 0;
}

bool Patterndatabase::setNumMoves(const Rubikscube &cube, const uint8_t numMoves){
    return this->setNumMoves(this->getDatabaseindex(cube), numMoves);
}

uint8_t Patterndatabase::getNumMoves(const uint32_t ind) const {
    return this->database.get(ind);
}

uint8_t Patterndatabase::getNumMoves(const Rubikscube &cube) const{
    return this-> getNumMoves(this->getDatabaseindex(cube));
}

size_t Patterndatabase::getSize() const{
    return this->size;
}

size_t Patterndatabase::getNumItems() const{
    return this->numItems;
}

bool Patterndatabase::isFull() const{
    return this->numItems == this->size;
}

void Patterndatabase::toFile(const string &filePath)const{
    ofstream writer(filePath, ios::out | ios::binary | ios::trunc);
    if(!writer.is_open())
        throw runtime_error("Failed to open pattern database for writing: " + filePath);

    writer.write(
        reinterpret_cast<const char*> (this->database.data()), 
        static_cast<streamsize>(this->database.storageSize())
    );
    if(!writer) throw runtime_error("Failed to write pattern database: " + filePath);
    writer.close();
}


bool Patterndatabase::fromFile(const string &filePath){
    ifstream reader(filePath, ios::in | ios::binary | ios::ate);
    
    if(!reader.is_open())
        return false;

    const streamoff fileSize = reader.tellg();

    if(fileSize < 0 || static_cast<size_t>(fileSize) != this->database.storageSize()){
        reader.close();
        throw runtime_error("Pattern database has an unexpected size: " + filePath);
    }

    reader.seekg(0, ios::beg);
    reader.read(
        reinterpret_cast<char*> (this->database.data()), 
        static_cast<streamsize>(this->database.storageSize())
    );
    if(!reader) throw runtime_error("Failed to read pattern database: " + filePath);

    reader.close();
    this->numItems = 0;
    for(size_t i=0; i<this->size; i++){
        if(this->database.get(i) != this->initValue) this->numItems++;
    }

    return true;
}

vector<uint8_t> Patterndatabase::inflate() const {
    vector<uint8_t> inflated;
    this->database.inflate(inflated);
    return inflated;
}

void Patterndatabase::reset() {
    this->database.reset(this->initValue);
    this->numItems = 0;
}

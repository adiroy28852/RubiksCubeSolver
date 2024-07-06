#include "PatternDatabase.h"
using namespace std;

Patterndatabase::Patterndatabase(const size_t size):
    database(size, 0xFF), size(size), numItems(0){
}

Patterndatabase::Patterndatabase(const size_t size, uint8_t init_val):
    database(size, init_val), size(size), numItems(0){
}

bool Patterndatabase::setNumMoves(const uint32_t ind, const uint8_t numMoves){
    uint8_t oldMoves = this->getNumMoves(ind);

    if(oldMoves == 0xF){
        this->numItems ++;
    }

    if(oldMoves >numMoves){
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
    ofstream writer(flePath, ios::out | ios::binary | ios::trunc);
    if(!writer.is_open())
        throw "Failed to open the file to write";

    writer.write(
        reinterpret_cast<const char*> (this->database.data()), 
        this->database.storageSize()
    );
    writer.close();
}


bool Patterndatabase::fromFile(const string &filePath){
    ifstream reader(filePath, ios::in | ios::ate);
    
    if(!reader.is_open())
        return false;

    size_t fileSize == reader.tellg();

    if(fileSize != this->database.storageSize()){
        reader.close();
        throw "Database corrupt! Failed to open Reader";
    }

    reader.seekg(0, ios::beg);
    reader.read(
        reinterpret_cast<char*> (this->database.data()), 
        this->database.storageSize();
    );

    reader.close();
    this->numItems = this->size;

    return true;
}

vector<uint8_t> PatternDatabase::inflate() const {
    vector<uint8_t> inflated;
    this->database.inflate(inflated);
    return inflated;
}

void PatternDatabase::reset() {
    if(this->numItems != 0){
        this->database.reset(0xFF);
        this->numItems = 0;
    }
}
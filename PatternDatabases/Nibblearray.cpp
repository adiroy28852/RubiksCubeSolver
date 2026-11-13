#include "Nibblearray.h"
using namespace std;

Nibblearray::Nibblearray(const size_t size, const uint8_t val):
    size(size), arr(size/2 + size%2, static_cast<uint8_t>((val & 0x0F) * 0x11)){
}

uint8_t Nibblearray::get (const size_t pos) const {
    size_t i= pos/2;
    assert(pos < this->size);
    uint8_t val= this->arr.at(i);

    if(pos&1){
        return val& 0x0F;
    }
    else{
        return val>>4;
    }
}

void Nibblearray::set(const size_t pos, const uint8_t val){
    size_t i = pos/2;
    uint8_t currVal = this->arr.at(i);
    assert(pos < this->size);
    assert(val <= 0x0F);

    if(pos&1){
        this->arr.at(i) = (currVal & 0xF0) | (val & 0x0F);
    }
    else{
        this->arr.at(i) = (currVal & 0x0F) | (val << 4);
    }
}

const unsigned char *Nibblearray::data() const{
    return this->arr.data();
}

unsigned char *Nibblearray::data(){
    return this->arr.data();
}

size_t Nibblearray::storageSize() const{
    return this->arr.size();
}

void Nibblearray::inflate(vector<uint8_t> &dest)const {
    dest.clear();
    dest.reserve(this->size);
    
    for(size_t i=0; i<this->size; i++) dest.push_back(this->get(i));
}

void Nibblearray::reset(const uint8_t val){
    fill(this->arr.begin(), this->arr.end(), static_cast<uint8_t>((val & 0x0F) * 0x11));
}

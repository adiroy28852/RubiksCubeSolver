#include "Rubikscube.h"

class Rubikscube1D : public Rubikscube{
    private:

    //convert a 3x3 face, each color cordinate from face x row x col to 1D array
    // => face*9 + row*3 + col

    static inline int getIdx(int ind, int row, int col){
        return (9*ind) + (3*row) + col;
    }
    
    void rotateFace(int ind){
        char temp_arr[9]={};
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp_arr[i*3+j] = cube[getIndex(ind, i, j)];
            }
        }

        for (int i = 0; i < 3; i++) {
            cube[getIndex(ind, 0, i)] = temp_arr[getIndex(0, 2 - i, 0)];
            cube[getIndex(ind, i, 2)] = temp_arr[getIndex(0, 0, i)];
            cube[getIndex(ind, 2, 2 - i)] = temp_arr[getIndex(0, i, 2)];
            cube[getIndex(ind, 2 - i, 0)] = temp_arr[getIndex(0, 2, 2 - i)];
        }

    }

    public:
    char cube[54]{};

    Rubikscube1D(){
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    cube[i*9 + j*3 + k]= getColorLetter(COLOR(i));
                }
            }
        }
    }
    
    COLOR getcolor(FACE face, unsigned row, unsigned col) const override{
        char color = cube[getIdx(int(face), int(row), int(col))];
        switch (color){
            case 'B':
                return COLOR::blue;
            case 'R':
                return COLOR::red;
            case 'G':
                return COLOR::green;
            case 'Y':
                return COLOR::yellow;
            case 'W':
                return COLOR::white;
            case 'O':
                return COLOR::orange;
                
        }
    }

    bool isSolved()const override{
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    if(this->cube[getIdx(i, j, k)] == getColorLetter(COLOR(i)))continue;
                    return 0;
                }
            }
        }
        return 1;
    }

    Rubikscube &u() override {
        this->rotateFace(0);

        char temp_arr[3]= {};

        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[getIndex(4, 0, i)];
            cube[getIndex(4, 0, i)] = cube[getIndex(1, 0, i)];
            cube[getIndex(1, 0, i)] = cube[getIndex(2, 0, i)];
            cube[getIndex(2, 0, i)] = cube[getIndex(3, 0, i)];
            cube[getIndex(3, 0, i)] = temp_arr[i];
        }

        return *this;
    }

    Rubikscube &uprime() override{

        this->u();
        this->u();
        this->u();

        return *this;
    }

    Rubikscube &u2() override{

        this->u();
        this->u();

        return *this;
    }

    Rubikscube &l() override{
        rotateFace(1);

        char temp_arr[3]= {};

        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[getIndex(0, i, 0)];
            cube[getIndex(0, i, 0)] = cube[getIndex(4, 2 - i, 2)];
            cube[getIndex(4, 2 - i, 2)] = cube[getIndex(5, i, 0)];
            cube[getIndex(5, i, 0)] = cube[getIndex(2, i, 0)];
            cube[getIndex(2, i, 0)] = temp_arr[i];
        }

        return *this;
    }

    Rubikscube &lprime() override{
        this->l();
        this->l();
        this->l();

        return *this;
    }

    Rubikscube &l2() override{
        this->l();
        this->l();

        return *this;
    }

    Rubikscube &f() override{
        this->rotateFace(2);

        char temp_arr[3]= {};
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[getIndex(0, 2, i)];
            cube[getIndex(0, 2, i)] = cube[getIndex(1, 2 - i, 2)];
            cube[getIndex(1, 2 - i, 2)] = cube[getIndex(5, 0, 2 - i)];
            cube[getIndex(5, 0, 2 - i)] = cube[getIndex(3, i, 0)];
            cube[getIndex(3, i, 0)] = temp_arr[i];
        }

        return *this;
    }

    Rubikscube &fprime override{
        this->f();
        this->f();
        this->f();

        return *this;
    }

    Rubikscube &f2 override{
        this->f();
        this->f();

        return *this;
    }

    Rubikscube &r() override{
        this->rotateFace(3);

        char temp_arr[3]={};
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[getIndex(0, 2 - i, 2)];
            cube[getIndex(0, 2 - i, 2)] = cube[getIndex(2, 2 - i, 2)];
            cube[getIndex(2, 2 - i, 2)] = cube[getIndex(5, 2 - i, 2)];
            cube[getIndex(5, 2 - i, 2)] = cube[getIndex(4, i, 0)];
            cube[getIndex(4, i, 0)] = temp_arr[i];
        }

        return *this;
    }

    Rubikscube &rprime() override{
        this->r();
        this->r();
        this->r();

        return *this;
    }

    Rubikscube &r2() override{
        this->r();
        this->r();

        return *this;
    }

    Rubikscube &b() override{
        this->rotateFace(4);

        char temp_arr[3]={};
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[getIndex(0, 0, 2 - i)];
            cube[getIndex(0, 0, 2 - i)] = cube[getIndex(3, 2 - i, 2)];
            cube[getIndex(3, 2 - i, 2)] = cube[getIndex(5, 2, i)];
            cube[getIndex(5, 2, i)] = cube[getIndex(1, i, 0)];
            cube[getIndex(1, i, 0)] = temp_arr[i];
        }

        return *this;

    }

    Rubikscube &bprime() override{
        this->b();
        this->b();
        this->b();
        
        return *this;
    }

    Rubikscube &b2() override{
        this->b();
        this->b();

        return *this;
    }

    Rubikscube &d() override{
        this->rotateFace(5);

        char temp_arr[3]={};
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[getIndex(2, 2, i)];
            cube[getIndex(2, 2, i)] = cube[getIndex(1, 2, i)];
            cube[getIndex(1, 2, i)] = cube[getIndex(4, 2, i)];
            cube[getIndex(4, 2, i)] = cube[getIndex(3, 2, i)];
            cube[getIndex(3, 2, i)] = temp_arr[i];
        }

        return *this;
    }

    Rubikscube &dprime override{
        this->d();
        this->d();
        this->d();

        return *this;
    }

    Rubikscube &d2 override{
        this->d();
        this->d();
        
        return *this;
    }

    bool operator ==(const Rubikscube1D &r1) const{
        for(int i=0; i<54; i++){
            if(cube[i]!= r1.cube[i])return 0;
        }
        return 1;
    }

    Rubikscube1D &operator =(const Rubikscube1D &r1){
        for(int i=0; i<54; i++){
            cube[i]= r1.cube[i];
        }
        return *this;
    }
};

struct Hash1D{
    size_t operator()(const Rubikscube1D &r1) const{
        string str="";
        for(int i=0; i<54; i++)str+= r1.cube[i];

        return hash<string>()(str);
    }
}
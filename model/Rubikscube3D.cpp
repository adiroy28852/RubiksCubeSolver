#include "Rubikscube.h"

class RubiksCube3D : public Rubikscube{
    private:
    void rotateFace(int ind){
        char temp[3][3] = {};
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i][j]= cube[ind][i][j];
            }
        }

        for(int i=0; i<3; i++)cube[ind][0][1]= temp[2-i][0];
        for(int i=0; i<3; i++)cube[ind][i][2]= temp[0][i];
        for(int i=0; i<3; i++)cube[ind][2][2-i]= temp[i][2];
        for(int i=0; i<3; i++)cube[ind][2-i][0]= temp[2][2-i];
    }
    public:
        char cube[6][3][3]{};

    RubiksCube3D{
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; i++){
                    cube[i][j][k]= getColorLetter(COLOR(i));
                }
            }
        }
    }
    COLOR getcolor(FACE face, unsigned row, unsigned col)const override{
        char color= cube[int(face)][row][col];
        switch (color){
            case 'B':
                return COLOR::blue;
            case 'O':
                return COLOR::orange;
            case 'R':
                return COLOR::red;
            case 'G':
                return COLOR::green;
            case 'Y':
                return COLOR::yellow;
            default:
                return COLOR::white;
        }
    }

    bool isSolved()const override{
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    if(this->cuble[i][j][k] == getColorLetter(getcolor(i)));
                    return 0;
                }
            }
            return 1;
        }
    }

    Rubikscube &u() override{
        this->rotateFace(0);

        char temp_arr[3] = {};
        //modified original from LakshayMittal's idea. yet to test
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[4][0][2 - i];
            cube[4][0][2 - i] = cube[1][0][2 - i];
            cube[1][0][2 - i] = cube[2][0][2 - i];
            cube[2][0][2 - i] = cube[3][0][2 - i];
            cube[3][0][2 - i] = temp_arr[i];
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
        this->rotateface(1);

        //also modified 
        char temp_arr[3]= {};
        for(int i=0; i<3; i++){
            temp_arr[i]= cube[0][i][0];
            cube[0][i][0]= cube[4][2-i][2];
            cube[4][2-i][2]= cube[5][i][0];
            cube[5][i][0]= cube[2][i][0];
            cube[2][i][0]= temp_arr[i];
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

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[0][2][i];
            cube[0][2][i] = cube[1][2 - i][2];
            cube[1][2 - i][2] = cube[5][0][2 - i];
            cube[5][0][2 - i] = cube[3][i][0];
            cube[3][i][0] = temp_arr[i];
        }

    }

    Rubikscube &fprime() override{
        this->f();
        this->f();
        this->f();

        return *this;
    }

    Rubikscube &f2() override{
        this->f();
        this->f();

        return *this;
    }

    Rubikscube &r() override{

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[0][2 - i][2];
            cube[0][2 - i][2] = cube[2][2 - i][2];
            cube[2][2 - i][2] = cube[5][2 - i][2];
            cube[5][2 - i][2] = cube[4][i][0];
            cube[4][i][0] = temp_arr[i];
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

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[0][0][2 - i];
            cube[0][0][2 - i] = cube[3][2 - i][2];
            cube[3][2 - i][2] = cube[5][2][i];
            cube[5][2][i] = cube[1][i][0];
            cube[1][i][0] = temp_arr[i];
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

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) {
            temp_arr[i] = cube[2][2][i];
            cube[2][2][i] = cube[1][2][i];
            cube[1][2][i] = cube[4][2][i];
            cube[4][2][i] = cube[3][2][i];
            cube[3][2][i] = temp_arr[i];
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

    bool operator ==(const RubiksCube3D &r1)const{
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; i++){
                    cube[i][j][k]= r1.cube[i][j][k];
                }
            }
        }
        return true;
    }

    RubiksCube3D &operator =(const RubiksCube3D &r1){
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    cube[i][j][k]= r1.cube[i][j][k];
                }
            }
        }
        return *this;
    }
};

struct Hash3d{
    size_t operator()(const RubiksCube3D &r1)const{
        string str="";
        for(int i=0; i<6; i++){
            for(int j=0; j<3; j++){
                for(int k=0; k<3; k++){
                    str+= r1.cube[i][j][k];
                }
            }
        }

        return hash<string>()(str);
    }
};
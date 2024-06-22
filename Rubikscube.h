#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
#ifdef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H

#include<bits/stdc++.h>
using namespace std;


class Rubikscube{
    public:
    enum class FACE{
        up, left, front, right, down, back
    };
    enum class COLOR{
        white, green, red, blue, orange, yellow
    };
    enum class MOVE{
        l, lprime, l2,
        r, rprime, r2, 
        d, dprime, d2, 
        f, fprime, f2, 
        b, bprime, b2, 
        u, uprime, u2
    };
    
    virtual COLOR getcolor(FACE face, unsigned row, unsigned col)const = 0;

    static char getColorLetter(COLOR color);

    virtual bool isSolved() const=0;

    static string getMove(MOVE ind);

    void print() const;

    vector<MOVE> randshuffle(unsigned int times);

    Rubikscube &move (MOVE ind);

    Rubikscube &invert (MOVE ind);

    virtual Rubikscube &f() = 0;
    virtual Rubikscube &fprime() = 0;
    virtual Rubikscube &f2() = 0;
    

    virtual Rubikscube &l() = 0;
    virtual Rubikscube &lprime() = 0;
    virtual Rubikscube &l2() = 0;
    

    virtual Rubikscube &r() = 0;
    virtual Rubikscube &rprime() = 0;
    virtual Rubikscube &r2() = 0;
    

    virtual Rubikscube &d() = 0;
    virtual Rubikscube &dprime() = 0;
    virtual Rubikscube &d2() = 0;
    

    virtual Rubikscube &u() = 0;
    virtual Rubikscube &uprime() = 0;
    virtual Rubikscube &u2() = 0;
    

    virtual Rubikscube &b() = 0;
    virtual Rubikscube &bprime() = 0;
    virtual Rubikscube &b2() = 0;
    
    string getCornerColorString(uint8_t ind) const;

    uint8_t getCornerIndex(uint8_t ind) const;

    uint8_t getCornerOrientation(uint8_t ind) const;

};












#endif
#include "Rubikscube.h"
#include <random>
// using namespace std;

char Rubikscube::getColorLetter(COLOR color){
    switch (color){
        case COLOR::blue:
            return 'B';
        case COLOR:: red:
            return 'R';
        case COLOR::green:
            return 'G';
        case COLOR::white:
            return 'W';
        case COLOR::yellow:
            return 'Y';
        case COLOR::orange:
            return 'O';
    }
}
string Rubikscube::getMove(MOVE ind){
    switch(ind){
        case MOVE::l:
            return "L";
        case MOVE::lprime:
            return "L'";
        case MOVE::l2:
            return "L2";
        case MOVE::r:
            return "R";
        case MOVE::rprime:
            return "R'";
        case MOVE::r2:
            return "R2";
        case MOVE::d:
            return "D";
        case MOVE::dprime:
            return "D'";
        case MOVE::d2:
            return "D2";
        case MOVE::u:
            return "U";
        case MOVE::uprime:
            return "U'";
        case MOVE::u2:
            return "U2";
        case MOVE::f:
            return "F";
        case MOVE::fprime:
            return "F'";
        case MOVE::f2:
            return "F2";
        case MOVE::b:
            return "B";
        case MOVE::bprime:
            return "B'";
        case MOVE::b2:
            return "B2";
    }
    return "?";
}

Rubikscube &Rubikscube::move(MOVE ind){
    switch(ind){
        case MOVE::l:
            return this->l();
        case MOVE::lprime:
            return this->lprime();
        case MOVE::l2:
            return this->l2();
        case MOVE::r:
            return this->r();
        case MOVE::rprime:
            return this->rprime();
        case MOVE::r2:
            return this->r2();
        case MOVE::f:
            return this->f();
        case MOVE::fprime:
            return this->fprime();
        case MOVE::f2:
            return this->f2();
        case MOVE::b:
            return this->b();
        case MOVE::bprime:
            return this->bprime();
        case MOVE::b2:
            return this->b2();
        case MOVE::u:
            return this->u();
        case MOVE::uprime:
            return this->uprime();
        case MOVE::u2:
            return this->u2();
        case MOVE::d:
            return this->d();
        case MOVE::dprime:
            return this->dprime();
        case MOVE::d2:
            return this->d2();
        
    }
}

Rubikscube &Rubikscube::invert(MOVE ind){
    switch(ind){
        case MOVE::l:
            return this->lprime();
        case MOVE::lprime:
            return this->l();
        case MOVE::l2:
            return this->l2();
        case MOVE::r:
            return this->rprime();
        case MOVE::rprime:
            return this->r();
        case MOVE::r2:
            return this->r2();
        case MOVE::f:
            return this->fprime();
        case MOVE::fprime:
            return this->f();
        case MOVE::f2:
            return this->f2();
        case MOVE::b:
            return this->bprime();
        case MOVE::bprime:
            return this->b();
        case MOVE::b2:
            return this->b2();
        case MOVE::u:
            return this->uprime();
        case MOVE::uprime:
            return this->u();
        case MOVE::u2:
            return this->u2();
        case MOVE::d:
            return this->dprime();
        case MOVE::dprime:
            return this->d();
        case MOVE::d2:
            return this->d2();
        
    }
}

void Rubikscube::print() const{
    cout<<"Rubiks cube layout \n\n";

    for(int row = 0; row<=2; row++){
        for(unsigned i=0; i<7; i++)cout<<" ";
        for(int col=0; col<=2; col++){
            cout<< getColorLetter(getcolor(FACE::up, row, col))<<' ';
        }
        
        cout<<endl;
    }
    cout<<endl;


    for(int row=0; row<=2; row++){

        for(int col=0; col<=2; col++){
            cout<<getColorLetter(getcolor(FACE::left, row, col))<<' ';
        }
        cout<<' ';
    }

    for(int row=0; row<=2; row++){

        for(int col=0; col<=2; col++){
            cout<<getColorLetter(getcolor(FACE::front, row, col))<<' ';
        }
        cout<<' ';
    }    for(int row=0; row<=2; row++){

        for(int col=0; col<=2; col++){
            cout<<getColorLetter(getcolor(FACE::right, row, col))<<' ';
        }
        cout<<' ';
    }    for(int row=0; row<=2; row++){

        for(int col=0; col<=2; col++){
            cout<<getColorLetter(getcolor(FACE::back, row, col))<<' ';
        }
        cout<<' ';
    }


    for(int row = 0; row<=2; row++){
        for(unsigned i=0; i<7; i++)cout<<" ";
        for(int col=0; col<=2; col++){
            cout<< getColorLetter(getcolor(FACE::down, row, col));
        }
        
        cout<<endl;
    }
    cout<<endl;
}

vector<Rubikscube::MOVE> Rubikscube :: randshuffle(unsigned int times){
    vector<MOVE> movesperformed;
    static mt19937 generator(random_device{}());
    uniform_int_distribution<unsigned int> distribution(0, 17);
    for(unsigned int i=0; i<times; i++){
        unsigned int select= distribution(generator);
        movesperformed.emplace_back(static_cast<MOVE>(select));
        this->move(static_cast<MOVE>(select));
    }
    return movesperformed;
}

string Rubikscube:: getCornerColorString(uint8_t ind)const {
    switch(ind){
        case 0:
            return string{getColorLetter(getcolor(FACE::up, 2, 2)),
                          getColorLetter(getcolor(FACE::right, 0, 0)),
                          getColorLetter(getcolor(FACE::front, 0, 2))};
        case 1:
            return string{getColorLetter(getcolor(FACE::up, 2, 0)),
                          getColorLetter(getcolor(FACE::front, 0, 0)),
                          getColorLetter(getcolor(FACE::left, 0, 2))};
        case 2:
            return string{getColorLetter(getcolor(FACE::up, 0, 0)),
                          getColorLetter(getcolor(FACE::left, 0, 0)),
                          getColorLetter(getcolor(FACE::back, 0, 2))};
        case 3:
            return string{getColorLetter(getcolor(FACE::up, 0, 2)),
                          getColorLetter(getcolor(FACE::back, 0, 0)),
                          getColorLetter(getcolor(FACE::right, 0, 2))};
        case 4:
            return string{getColorLetter(getcolor(FACE::down, 0, 2)),
                          getColorLetter(getcolor(FACE::front, 2, 2)),
                          getColorLetter(getcolor(FACE::right, 2, 0))};
        case 5:
            return string{getColorLetter(getcolor(FACE::down, 0, 0)),
                          getColorLetter(getcolor(FACE::left, 2, 2)),
                          getColorLetter(getcolor(FACE::front, 2, 0))};
        case 6:
            return string{getColorLetter(getcolor(FACE::down, 2, 2)),
                          getColorLetter(getcolor(FACE::right, 2, 2)),
                          getColorLetter(getcolor(FACE::back, 2, 0))};
        case 7:
            return string{getColorLetter(getcolor(FACE::down, 2, 0)),
                          getColorLetter(getcolor(FACE::back, 2, 2)),
                          getColorLetter(getcolor(FACE::left, 2, 0))};
    }
    return {};
}

uint8_t Rubikscube::getCornerIndex(uint8_t ind)const{
    string corner= getCornerColorString(ind);

    uint8_t ret=0;
    for( auto c: corner){
        if(c!= 'W' and c!= 'Y')continue;
        if(c=='Y') ret|= (1<<2);
    }
    for( auto c: corner){
        if(c!= 'R' and c!= 'O')continue;
        if(c=='O') ret|= (1<<1);
    }
    for( auto c: corner){
        if(c!= 'B' and c!= 'G')continue;
        if(c=='G') ret|= (1<<0);
    }
    
    return ret;
}

uint8_t Rubikscube::getCornerOrientation(uint8_t ind)const{
    string corner= getCornerColorString(ind);
    if(corner.size() != 3)return 0;

    string str= "";

    for(auto c: corner){
        if(c!= 'W' and c!='Y')continue;
        str.push_back(c);
    }

    if(corner[1]== str[0])return 1;

    else if(corner[2] == str[0])return 2;
    
    else return 0;
}

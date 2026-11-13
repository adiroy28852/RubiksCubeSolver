#include "Rubikscube.h"
#include "CubeMoves.h"
#include <array>


class RubikscubeBitboard : public Rubikscube{
    private:

    uint64_t solved_sideconfig[6]{};
    static constexpr int arr[3][3]= {{0, 1, 2},
                                     {7, 8, 3},
                                     {6, 5, 4}};

    uint64_t one_8= (1<<8)-1;

    struct StickerMove{
        int destinationFace;
        int destinationPosition;
        int sourceFace;
        int sourcePosition;
    };

    typedef array<StickerMove, 20> MoveMap;

    static MoveMap createMoveMap(int face){
        MoveMap moveMap{};
        int moveIndex = 0;
        const int faceIndex[6] = {0, 1, 2, 3, 5, 4};
        const int nx[6] = {0, -1, 0, 1, 0, 0};
        const int ny[6] = {1, 0, 0, 0, -1, 0};
        const int nz[6] = {0, 0, 1, 0, 0, -1};
        for(int sourceFace=0; sourceFace<6; sourceFace++){
            for(int row=0; row<3; row++){
                for(int col=0; col<3; col++){
                    cube_moves::Facelet facelet = cube_moves::getFacelet(sourceFace, row, col);
                    if(facelet.x*nx[face] + facelet.y*ny[face] + facelet.z*nz[face] != 1) continue;
                    const int sourcePosition = arr[row][col];
                    if(sourcePosition == 8) continue;
                    cube_moves::rotate(facelet, nx[face], ny[face], nz[face]);
                    const int destinationIndex = cube_moves::getIndex(facelet);
                    const int destinationRow = (destinationIndex % 9) / 3;
                    const int destinationCol = destinationIndex % 3;
                    const int destinationPosition = arr[destinationRow][destinationCol];
                    moveMap[moveIndex++] = {faceIndex[destinationIndex / 9], destinationPosition,
                                            faceIndex[sourceFace], sourcePosition};
                }
            }
        }
        return moveMap;
    }

    static const MoveMap &getMoveMap(int face){
        static const array<MoveMap, 6> moveMaps = []{
            array<MoveMap, 6> maps{};
            for(int index=0; index<6; index++) maps[index] = createMoveMap(index);
            return maps;
        }();
        return moveMaps[face];
    }

    void rotateFace(int ind){
        uint64_t side= bitboard[ind];
        side= side>>(8*6);
        bitboard[ind]= (bitboard[ind]<<16) | (side);
    }

    void rotateSide(int s1, int s1_1, int s1_2, int s1_3, int s2, int s2_1, int s2_2, int s2_3){
        uint64_t clr1= (bitboard[s2] & (one_8 << (8* s2_1))) >> (8 * s2_1);
        uint64_t clr2= (bitboard[s2] & (one_8 << (8* s2_2))) >> (8 * s2_2);
        uint64_t clr3= (bitboard[s2] & (one_8 << (8* s2_3))) >> (8 * s2_3);

        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_1))) | (clr1 << (8 * s1_1));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_2))) | (clr2 << (8 * s1_2));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_3))) | (clr3 << (8 * s1_3));
                
    }

    void turn(int face, int turns){
        const MoveMap &moveMap = getMoveMap(face);
        while(turns-- > 0){
            uint64_t oldBitboard[6];
            for(int side=0; side<6; side++) oldBitboard[side] = bitboard[side];
            for(const StickerMove &move : moveMap){
                const uint64_t color = (oldBitboard[move.sourceFace] >> (8 * move.sourcePosition)) & one_8;
                const uint64_t mask = one_8 << (8 * move.destinationPosition);
                bitboard[move.destinationFace] =
                    (bitboard[move.destinationFace] & ~mask) | (color << (8 * move.destinationPosition));
            }
        }
    }

    int get5bitCorner(string corner){
        int ret=0;
        string actual_str;
        for(auto c : corner){
            if(c != 'W' and c != 'Y')continue;
            actual_str.push_back(c);
            if(c == 'Y'){
                ret|= (1<<2);
            }
        }

        for(auto c : corner){
            if(c != 'R' and c != 'O')continue;
            actual_str.push_back(c);
            if(c == 'O'){
                ret|= (1<<1);
            }
        }

        for(auto c : corner){
            if(c != 'B' and c != 'G')continue;
            actual_str.push_back(c);
            if(c == 'G'){
                ret|= (1<<0);
            }
        }

        if(corner[1] == actual_str[0]){
            ret|= (1<<3);
        }
        else if(corner[2] == actual_str[0]){
            ret |= (1<<4);
        }
        return ret;
    }

    public:
    uint64_t bitboard[6]{};

    RubikscubeBitboard(){
        for(int side=0; side < 6; side++){
            uint64_t clr= 1<<side;
            bitboard[side]= 0;
            for(int faceIdx=0; faceIdx<8; faceIdx++){
                bitboard[side] |= clr<<(8*faceIdx);
            }
            solved_sideconfig[side]= bitboard[side];
        }
    }

    RubikscubeBitboard(const RubikscubeBitboard &r1) = default;

    COLOR getcolor(FACE face, unsigned row, unsigned col) const override {
        int faceIndex = static_cast<int>(face);
        if(face == FACE::down) faceIndex = 5;
        else if(face == FACE::back) faceIndex = 4;
        int idx= arr[row][col];
        if (idx==8) return (COLOR)faceIndex;
        
        uint64_t side= bitboard[faceIndex];
        uint64_t color= (side>> (8* idx)) & one_8;

        int bit_pos = 0;
        while(color != 0){
            color = color>>1;
            bit_pos++;
        }
        return (COLOR)(bit_pos-1);
    }

    bool isSolved() const override{
        for(int i=0; i<6; i++){
            if(solved_sideconfig[i] != bitboard[i])return false;
        }
        return true;
    }

    Rubikscube &u() override{
        this->turn(0, 1);
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
        this->turn(1, 1);
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
        this->turn(2, 1);
        return *this;
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
        this->turn(3, 1);
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
        this->turn(5, 1);
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
        this->turn(4, 1);
        return *this;
    }

    Rubikscube &dprime() override{
        this->d();
        this->d();
        this->d();
        
        return *this;
    }

    Rubikscube &d2() override{
        this->d();
        this->d();

        return *this;
    }

    bool operator == (const RubikscubeBitboard &r1) const{
        for(int i=0; i<6; i++){
            if(bitboard[i] != r1.bitboard[i])return false;
        }
        return true;
    }

    RubikscubeBitboard &operator =(const RubikscubeBitboard &r1){
        for(int i=0; i<6; i++){
            bitboard[i]= r1.bitboard[i];
        }
        return *this;
    }

    uint64_t getCorners(){
        uint64_t ret=0;
        
        string top_front_right = "";
        top_front_right += getColorLetter(getcolor(FACE::up, 2, 2));
        top_front_right += getColorLetter(getcolor(FACE::front, 0, 2));
        top_front_right += getColorLetter(getcolor(FACE::right, 0, 0));

        string top_front_left = "";
        top_front_left += getColorLetter(getcolor(FACE::up, 2, 0));
        top_front_left += getColorLetter(getcolor(FACE::front, 0, 0));
        top_front_left += getColorLetter(getcolor(FACE::left, 0, 2));

        string top_back_left = "";
        top_back_left += getColorLetter(getcolor(FACE::up, 0, 0));
        top_back_left += getColorLetter(getcolor(FACE::back, 0, 2));
        top_back_left += getColorLetter(getcolor(FACE::left, 0, 0));

        string top_back_right = "";
        top_back_right += getColorLetter(getcolor(FACE::up, 0, 2));
        top_back_right += getColorLetter(getcolor(FACE::back, 0, 0));
        top_back_right += getColorLetter(getcolor(FACE::right, 0, 2));

        string bottom_front_right = "";
        bottom_front_right += getColorLetter(getcolor(FACE::down, 0, 2));
        bottom_front_right += getColorLetter(getcolor(FACE::front, 2, 2));
        bottom_front_right += getColorLetter(getcolor(FACE::right, 2, 0));

        string bottom_front_left = "";
        bottom_front_left += getColorLetter(getcolor(FACE::down, 0, 0));
        bottom_front_left += getColorLetter(getcolor(FACE::front, 2, 0));
        bottom_front_left += getColorLetter(getcolor(FACE::left, 2, 2));

        string bottom_back_right = "";
        bottom_back_right += getColorLetter(getcolor(FACE::down, 2, 2));
        bottom_back_right += getColorLetter(getcolor(FACE::back, 2, 0));
        bottom_back_right += getColorLetter(getcolor(FACE::right, 2, 2));

        string bottom_back_left = "";
        bottom_back_left += getColorLetter(getcolor(FACE::down, 2, 0));
        bottom_back_left += getColorLetter(getcolor(FACE::back, 2, 2));
        bottom_back_left += getColorLetter(getcolor(FACE::left, 2, 0));
        

        ret |= get5bitCorner(top_front_right);
        ret = ret << 5;

        ret |= get5bitCorner(top_front_left);
        ret = ret << 5;

        ret |= get5bitCorner(top_back_right);
        ret = ret << 5;

        ret |= get5bitCorner(top_back_left);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_front_right);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_front_left);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_back_right);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_back_left);
        ret = ret << 5;


        return ret;
    }

};



struct HashBitboard{
    size_t operator()(const RubikscubeBitboard &r1) const{
        uint64_t final_hash = r1.bitboard[0];
        for(int i=1; i<6; i++)final_hash^= r1.bitboard[i];
        return (size_t)final_hash;
    }
};

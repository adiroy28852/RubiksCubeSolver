#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

#include "../model/Rubikscube.cpp"
#include "../model/Rubikscube1D.cpp"
#include "../model/Rubikscube3D.cpp"
#include "../model/RubikscubeBitboard.cpp"
#include "../PatternDatabases/Nibblearray.h"
#include "../PatternDatabases/Permutationindexer.h"
#include "../PatternDatabases/Patterndatabase.h"
#include "../PatternDatabases/CornerPatternDB.h"
#include "../Solver/BFSsolver.h"
#include "../Solver/DFSsolver.h"
#include "../Solver/IDDFSsolver.h"

class SmallPatternDB : public Patterndatabase {
public:
    SmallPatternDB() : Patterndatabase(10) {}
    uint32_t getDatabaseindex(const Rubikscube &) const override { return 0; }
};

template <typename T, typename U>
void compareCubes(const T &first, const U &second) {
    for (int face = 0; face < 6; ++face) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                assert(first.getcolor(Rubikscube::FACE(face), row, col) ==
                       second.getcolor(Rubikscube::FACE(face), row, col));
            }
        }
    }
}

void testCubeMoves() {
    for (int moveIndex = 0; moveIndex < 18; ++moveIndex) {
        Rubikscube1D cube1D;
        RubiksCube3D cube3D;
        RubikscubeBitboard bitboard;
        const Rubikscube::MOVE move = static_cast<Rubikscube::MOVE>(moveIndex);
        cube1D.move(move);
        cube3D.move(move);
        bitboard.move(move);
        compareCubes(cube1D, cube3D);
        compareCubes(cube1D, bitboard);
        cube1D.invert(move);
        cube3D.invert(move);
        bitboard.invert(move);
        assert(cube1D.isSolved());
        assert(cube3D.isSolved());
        assert(bitboard.isSolved());
    }

    const Rubikscube::MOVE scramble[] = {
        Rubikscube::MOVE::l, Rubikscube::MOVE::u, Rubikscube::MOVE::b2,
        Rubikscube::MOVE::rprime, Rubikscube::MOVE::f
    };
    Rubikscube1D cube1D;
    RubiksCube3D cube3D;
    RubikscubeBitboard bitboard;
    for (Rubikscube::MOVE move : scramble) {
        cube1D.move(move);
        cube3D.move(move);
        bitboard.move(move);
    }
    compareCubes(cube1D, cube3D);
    compareCubes(cube1D, bitboard);

    std::array<bool, 8> seen{};
    int orientationSum = 0;
    for (uint8_t corner = 0; corner < 8; ++corner) {
        const uint8_t index = bitboard.getCornerIndex(corner);
        assert(index < 8 && !seen[index]);
        seen[index] = true;
        orientationSum += bitboard.getCornerOrientation(corner);
    }
    assert(orientationSum % 3 == 0);
}

void testNibbleArray() {
    Nibblearray array(9);
    for (size_t index = 0; index < 9; ++index) assert(array.get(index) == 0x0F);
    for (size_t index = 0; index < 9; ++index) array.set(index, static_cast<uint8_t>(index));
    for (size_t index = 0; index < 9; ++index) assert(array.get(index) == index);
    assert(array.storageSize() == 5);
    array.reset(0x09);
    for (size_t index = 0; index < 9; ++index) assert(array.get(index) == 9);
}

void testPermutationIndexer() {
    Permutationindexer<4> indexer;
    std::array<uint8_t, 4> permutation = {0, 1, 2, 3};
    std::array<bool, 24> seen{};
    do {
        const uint32_t rank = indexer.rank(permutation);
        assert(rank < seen.size() && !seen[rank]);
        seen[rank] = true;
    } while (std::next_permutation(permutation.begin(), permutation.end()));
    for (bool rankSeen : seen) assert(rankSeen);
}

void testPatternDatabaseFiles() {
    const std::string fileName = "/tmp/rubiks-cube-pattern-db-test.bin";
    SmallPatternDB database;
    assert(database.getNumMoves(0) == 0x0F);
    assert(database.setNumMoves(0, 3));
    assert(!database.setNumMoves(0, 4));
    assert(database.getNumItems() == 1);
    database.toFile(fileName);

    SmallPatternDB loaded;
    assert(loaded.fromFile(fileName));
    assert(loaded.getNumMoves(0) == 3);
    assert(loaded.getNumMoves(1) == 0x0F);
    assert(loaded.getNumItems() == 1);
    loaded.reset();
    assert(loaded.getNumMoves(0) == 0x0F);
    assert(loaded.getNumItems() == 0);
    std::remove(fileName.c_str());
}

void testCornerPatternDatabase() {
    CornerPatternDB database;
    RubikscubeBitboard cube;
    assert(database.getSize() == 88179840);
    assert(database.getNumMoves(cube) == 9);
    assert(database.setNumMoves(cube, 0));
    assert(database.getNumMoves(cube) == 0);
    assert(database.getNumItems() == 1);
    database.reset();
    assert(database.getNumMoves(cube) == 9);
    assert(database.getNumItems() == 0);
    for (int moveIndex = 0; moveIndex < 18; ++moveIndex) {
        RubikscubeBitboard movedCube;
        movedCube.move(static_cast<Rubikscube::MOVE>(moveIndex));
        assert(database.getDatabaseindex(movedCube) < database.getSize());
    }
}

template <typename Solver>
void assertSolverSolution(Solver &solver, RubikscubeBitboard cube) {
    const std::vector<Rubikscube::MOVE> solution = solver.solve();
    for (Rubikscube::MOVE move : solution) cube.move(move);
    assert(cube.isSolved());
}

void testSearchSolvers() {
    RubikscubeBitboard cube;
    cube.move(Rubikscube::MOVE::l);
    cube.move(Rubikscube::MOVE::u);

    BFSsolver<RubikscubeBitboard, HashBitboard> breadthFirst(cube);
    assertSolverSolution(breadthFirst, cube);

    DFSsolver<RubikscubeBitboard, HashBitboard> depthFirst(cube, 2);
    assertSolverSolution(depthFirst, cube);

    IDDFSsolver<RubikscubeBitboard, HashBitboard> iterativeDeepening(cube, 2);
    assertSolverSolution(iterativeDeepening, cube);
}

int main() {
    testCubeMoves();
    testNibbleArray();
    testPermutationIndexer();
    testPatternDatabaseFiles();
    testCornerPatternDatabase();
    testSearchSolvers();
}

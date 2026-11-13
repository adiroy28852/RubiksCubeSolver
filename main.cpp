#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "model/Rubikscube.h"
#include "model/Rubikscube1D.cpp"
#include "model/Rubikscube3D.cpp"
#include "model/RubikscubeBitboard.cpp"
#include "PatternDatabases/CornerDBmaker.h"
#include "Solver/IDAStarsolver.h"

namespace {

void printUsage(const char *programName) {
    std::cout << "Usage:\n"
              << "  " << programName << " --generate-db <database-file>\n"
              << "  " << programName << " --solve <database-file> [moves...]\n"
              << "  " << programName << " --shuffle <move-count> <database-file>\n\n"
              << "Moves use standard notation: U, U', U2, R, R', R2, and so on.\n";
}

bool parseMove(const std::string &moveText, Rubikscube::MOVE &move) {
    static const std::string moveNames[18] = {
        "L", "L'", "L2", "R", "R'", "R2", "D", "D'", "D2",
        "F", "F'", "F2", "B", "B'", "B2", "U", "U'", "U2"
    };
    for (int index = 0; index < 18; ++index) {
        if (moveText == moveNames[index]) {
            move = static_cast<Rubikscube::MOVE>(index);
            return true;
        }
    }
    return false;
}

void printMoves(const std::vector<Rubikscube::MOVE> &moves) {
    if (moves.empty()) {
        std::cout << "(already solved)";
        return;
    }
    for (Rubikscube::MOVE move : moves) std::cout << Rubikscube::getMove(move) << ' ';
}

int solveCube(RubikscubeBitboard cube, const std::string &databaseFile) {
    std::cout << "Cube before solving:\n";
    cube.print();
    IDAStarsolver<RubikscubeBitboard, HashBitboard> solver(cube, databaseFile);
    const std::vector<Rubikscube::MOVE> solution = solver.solve();
    RubikscubeBitboard verifiedCube = cube;
    for (Rubikscube::MOVE move : solution) verifiedCube.move(move);
    std::cout << "Solution: ";
    printMoves(solution);
    std::cout << '\n';
    verifiedCube.print();
    return verifiedCube.isSolved() ? EXIT_SUCCESS : EXIT_FAILURE;
}

}

int main(int argc, char **argv) {
    if (argc < 2 || std::string(argv[1]) == "--help") {
        printUsage(argv[0]);
        return argc < 2 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    try {
        const std::string command = argv[1];
        if (command == "--generate-db") {
            if (argc != 3) {
                printUsage(argv[0]);
                return EXIT_FAILURE;
            }
            CornerDBMaker maker(argv[2], 9);
            maker.bfsAndStore();
            std::cout << "Corner pattern database written to " << argv[2] << '\n';
            return EXIT_SUCCESS;
        }

        if (command == "--solve") {
            if (argc < 3) {
                printUsage(argv[0]);
                return EXIT_FAILURE;
            }
            RubikscubeBitboard cube;
            std::vector<Rubikscube::MOVE> scramble;
            for (int index = 3; index < argc; ++index) {
                Rubikscube::MOVE move;
                if (!parseMove(argv[index], move)) {
                    std::cerr << "Unknown move: " << argv[index] << '\n';
                    return EXIT_FAILURE;
                }
                cube.move(move);
                scramble.push_back(move);
            }
            std::cout << "Scramble: ";
            printMoves(scramble);
            std::cout << '\n';
            return solveCube(cube, argv[2]);
        }

        if (command == "--shuffle") {
            if (argc != 4) {
                printUsage(argv[0]);
                return EXIT_FAILURE;
            }
            const int moveCount = std::stoi(argv[2]);
            if (moveCount < 0) throw std::invalid_argument("move count must be nonnegative");
            RubikscubeBitboard cube;
            const std::vector<Rubikscube::MOVE> scramble = cube.randshuffle(static_cast<unsigned int>(moveCount));
            std::cout << "Scramble: ";
            printMoves(scramble);
            std::cout << '\n';
            return solveCube(cube, argv[3]);
        }

        printUsage(argv[0]);
        return EXIT_FAILURE;
    } catch (const std::exception &error) {
        std::cerr << "Error: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}

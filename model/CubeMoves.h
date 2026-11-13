#ifndef RUBIKS_CUBE_SOLVER_CUBEMOVES_H
#define RUBIKS_CUBE_SOLVER_CUBEMOVES_H

#include <array>

namespace cube_moves {

struct Facelet {
    int x, y, z;
    int nx, ny, nz;
};

inline Facelet getFacelet(int face, int row, int col) {
    switch (face) {
        case 0: return {col - 1, 1, row - 1, 0, 1, 0};
        case 1: return {-1, 1 - row, col - 1, -1, 0, 0};
        case 2: return {col - 1, 1 - row, 1, 0, 0, 1};
        case 3: return {1, 1 - row, 1 - col, 1, 0, 0};
        case 4: return {col - 1, -1, 1 - row, 0, -1, 0};
        default: return {1 - col, 1 - row, -1, 0, 0, -1};
    }
}

inline int getIndex(const Facelet &facelet) {
    int face, row, col;
    if (facelet.ny == 1) {
        face = 0; row = facelet.z + 1; col = facelet.x + 1;
    } else if (facelet.nx == -1) {
        face = 1; row = 1 - facelet.y; col = facelet.z + 1;
    } else if (facelet.nz == 1) {
        face = 2; row = 1 - facelet.y; col = facelet.x + 1;
    } else if (facelet.nx == 1) {
        face = 3; row = 1 - facelet.y; col = 1 - facelet.z;
    } else if (facelet.ny == -1) {
        face = 4; row = 1 - facelet.z; col = facelet.x + 1;
    } else {
        face = 5; row = 1 - facelet.y; col = 1 - facelet.x;
    }
    return face * 9 + row * 3 + col;
}

inline void rotate(Facelet &facelet, int nx, int ny, int nz) {
    const int positionDot = facelet.x * nx + facelet.y * ny + facelet.z * nz;
    const int normalDot = facelet.nx * nx + facelet.ny * ny + facelet.nz * nz;
    const int x = -ny * facelet.z + nz * facelet.y + nx * positionDot;
    const int y = -nz * facelet.x + nx * facelet.z + ny * positionDot;
    const int z = -nx * facelet.y + ny * facelet.x + nz * positionDot;
    const int normalX = -ny * facelet.nz + nz * facelet.ny + nx * normalDot;
    const int normalY = -nz * facelet.nx + nx * facelet.nz + ny * normalDot;
    const int normalZ = -nx * facelet.ny + ny * facelet.nx + nz * normalDot;
    facelet = {x, y, z, normalX, normalY, normalZ};
}

inline void apply(std::array<char, 54> &cube, int face, int turns) {
    static const int normals[6][3] = {
        {0, 1, 0}, {-1, 0, 0}, {0, 0, 1}, {1, 0, 0}, {0, -1, 0}, {0, 0, -1}
    };
    while (turns-- > 0) {
        std::array<char, 54> moved = cube;
        const int nx = normals[face][0];
        const int ny = normals[face][1];
        const int nz = normals[face][2];
        for (int sourceFace = 0; sourceFace < 6; ++sourceFace) {
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    Facelet facelet = getFacelet(sourceFace, row, col);
                    if (facelet.x * nx + facelet.y * ny + facelet.z * nz == 1) {
                        rotate(facelet, nx, ny, nz);
                    }
                    moved[getIndex(facelet)] = cube[sourceFace * 9 + row * 3 + col];
                }
            }
        }
        cube = moved;
    }
}

}

#endif

# Rubik's Cube Solver

This project contains 1D, 3D, and bitboard cube representations, depth limited
search solvers, and an IDA* solver guided by a corner pattern database.

## Build

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Create a corner database

```sh
./build/rubiks_cube_solver --generate-db corner-depth8.bin
```

The generator stores corner distances through depth 8. The resulting file is
about 42 MiB. Keep it available when running IDA*.

## Solve a cube

Pass a scramble as standard move tokens:

```sh
./build/rubiks_cube_solver --solve corner-depth8.bin R U R' U'
```

Or generate a random scramble and solve it:

```sh
./build/rubiks_cube_solver --shuffle 13 corner-depth8.bin
```

Run `./build/rubiks_cube_solver --help` for the command summary.


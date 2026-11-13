cmake_minimum_required(VERSION 3.16)
project(RubiksCubeSolver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(rubiks_cube_solver
    main.cpp
    model/Rubikscube.cpp
    PatternDatabases/CornerDBmaker.cpp
    PatternDatabases/CornerPatternDB.cpp
    PatternDatabases/Nibblearray.cpp
    PatternDatabases/Patterndatabase.cpp
    PatternDatabases/math.cpp
)

target_compile_options(rubiks_cube_solver PRIVATE -Wall -Wextra -Wpedantic)

include(CTest)
if(BUILD_TESTING)
    add_executable(rubiks_cube_tests
        tests/solver_tests.cpp
        PatternDatabases/Nibblearray.cpp
        PatternDatabases/Patterndatabase.cpp
        PatternDatabases/CornerPatternDB.cpp
        PatternDatabases/math.cpp
    )
    target_compile_options(rubiks_cube_tests PRIVATE -Wall -Wextra -Wpedantic)
    add_test(NAME rubiks_cube_tests COMMAND rubiks_cube_tests)
endif()

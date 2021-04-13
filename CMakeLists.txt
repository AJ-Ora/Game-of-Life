# CMakeList.txt : CMake project for Game-of-Life, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Game-of-Life")

# Specify the C++ standard
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Add source to this project's executable.
add_executable (Game-of-Life "Game-of-Life.cpp"  "source/LifeBoard.cpp" "source/LifeBoard.h")

# TODO: Add tests and install targets if needed.

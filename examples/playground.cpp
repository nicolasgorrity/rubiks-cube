#include <iostream>
#include "cube.hpp"


int main(int argc, char* argv[]) {
    rubiks::Cube cube(20);
    std::cout << cube << std::endl;
    return 0;
}
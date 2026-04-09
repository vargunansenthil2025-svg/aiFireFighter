#include "vision_sim.h"
#include <iostream>

void renderSimulation(int roomSize, int robotX, int robotY, int fireX, int fireY) {
    std::cout << "\n Room Size: " << roomSize << "x" << roomSize << std::endl;
    std::cout << " Robot at: (" << robotX << "," << robotY << ")" << std::endl;
    std::cout << " Fire at: (" << fireX << "," << fireY << ")" << std::endl;
}
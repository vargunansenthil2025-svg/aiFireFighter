#ifndef VISION_SIM_H
#define VISION_SIM_H

#include <vector>

void renderSimulation(int roomSize, int robotX, int robotY, int fireX, int fireY,
                      const std::vector<std::vector<bool>> &visited);

#endif
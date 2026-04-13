#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <queue>

bool moveRobotTowardsFire(int &robotX, int &robotY, int fireX, int fireY,
                          std::vector<std::vector<bool>> &visited);

#endif
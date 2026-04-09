#include "pathfinding.h"
bool moveRobotTowardsFire(int &robotX, int &robotY, int fireX, int fireY) {
    if (robotX == fireX && robotY == fireY) {
        return true; 
    }

    if (robotX < fireX) {
        robotX++; 
    } else if (robotX > fireX) {
        robotX--; 
    } else if (robotY < fireY) {
        robotY++; 
    } else if (robotY > fireY) {
        robotY--; 
    }

    return false; 
}

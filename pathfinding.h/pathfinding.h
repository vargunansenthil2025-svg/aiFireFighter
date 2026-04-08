<<<<<<< HEAD
#ifdef PATHFINDING_H
#define PATHFINDING_H

bool moveRobotFire(int &robotX,int &robotY,intFireX,int fire y);
#endif
bool moveRobotTowardsFire(int &robotX, int &robotY, int fireX, int fireY) {
 if(robotX == fireX && robotY == fireY){
    return true;
 }

 if(robotx < firex) {
    robotX++;
 } else if (robotX > fireX){
     robotX--;
 } else if (robotY < fireY) {
     robotY++;
 } else f (robotY > fireY) {
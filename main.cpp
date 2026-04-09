#include <iostream>
#include <thread>
#include <chrono>
#include "vision_sim.h"
#include "pathfinding.h"
#include "iot_logger.h"

using namespace std;

int main() {
    int roomSize, robotX, robotY, fireX, fireY;
    cout << "=== AI Fire Robot Simulator ===\n";
    cout << "Enter Room Size : ";
    cin >> roomSize;
    cout << "Enter Robot Start X & Y : ";
    cin >> robotX >> robotY;
    cout << "Enter Fire Location X & Y : ";
    cin >> fireX >> fireY;
    initIoTLogger();
    logEvent("System Started. Room size: " + to_string(roomSize));
    logEvent("Fire detected at: [" + to_string(fireX) + ", " + to_string(fireY) + "]");
    bool fireExtinguished = false;

    while (!fireExtinguished) {

        renderSimulation(roomSize, robotX, robotY, fireX, fireY);
        fireExtinguished = moveRobotTowardsFire(robotX, robotY, fireX, fireY);
        logEvent("Robot moved to: [" + to_string(robotX) + ", " + to_string(robotY) + "]");
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    logEvent("CRITICAL: Fire Reached. Extinguishing sequence activated.");
    cout << "\n[SUCCESS] Fire Reached and Extinguished!\n";
    renderSimulation(roomSize, robotX, robotY, fireX, fireY);
    
    return 0;
}

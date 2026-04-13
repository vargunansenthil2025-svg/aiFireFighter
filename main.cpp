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
    std::vector<std::vector<bool>> visited(roomSize, std::vector<bool>(roomSize, false));
    std::vector<pair<int, int>> pathCoordinates;
    
    // Mark initial robot position and store it
    visited[robotY][robotX] = true;
    pathCoordinates.push_back({robotX, robotY});

    while (!fireExtinguished) {
        renderSimulation(roomSize, robotX, robotY, fireX, fireY, visited);
        cout << "\n>> Robot at: [" << robotX << ", " << robotY << "]" << endl;
        fireExtinguished = moveRobotTowardsFire(robotX, robotY, fireX, fireY, visited);
        if (!fireExtinguished) {
            pathCoordinates.push_back({robotX, robotY});
        }
        logEvent("Robot moved to: [" + to_string(robotX) + ", " + to_string(robotY) + "]");
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    // Store final position before extinguishing
    pathCoordinates.push_back({robotX, robotY});
    
    // Robot is now one block away from fire - extinguish it
    cout << ">> Robot at: [" << robotX << ", " << robotY << "]" << endl;
    cout << ">> Fire at: [" << fireX << ", " << fireY << "]" << endl;
    logEvent("Robot positioned. Range to fire: 1 block. Initiating extinguishing sequence.");
    cout << "\n*** ACTIVATING FIRE EXTINGUISHER ***\n";
    
    // Mark fire location as visited to show in path
    visited[fireY][fireX] = true;
    
    this_thread::sleep_for(chrono::milliseconds(1000));
    renderSimulation(roomSize, robotX, robotY, fireX, fireY, visited);
    
    logEvent("CRITICAL: Fire EXTINGUISHED!");
    cout << "\n[SUCCESS] Fire Extinguished!\n";
    
    // Display complete robot movement path (after final grid)
    cout << "\n\n========== ROBOT MOVEMENT PATH ==========\n";
    for (size_t i = 0; i < pathCoordinates.size(); i++) {
        cout << "(" << pathCoordinates[i].first << "," << pathCoordinates[i].second << ")";
        if (i < pathCoordinates.size() - 1) {
            cout << ", ";
        }
    }
    cout << "\n\nStart Position: (" << pathCoordinates.front().first << "," << pathCoordinates.front().second << ")\n";
    cout << "Final Position: (" << pathCoordinates.back().first << "," << pathCoordinates.back().second << ")\n";
    cout << "=========================================\n";
    
    return 0;
}

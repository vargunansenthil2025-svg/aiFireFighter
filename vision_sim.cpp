#include "vision_sim.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

static void clearConsole() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif
}

void renderSimulation(int roomSize, int robotX, int robotY, int fireX, int fireY,
                      const std::vector<std::vector<bool>> &visited) {
    clearConsole();

    std::cout << "=== AIfirefighter  grid view ===\n";
    std::cout << " Room " << roomSize << "x" << roomSize
              << "   Robot (" << robotX << "," << robotY << ")"
              << "   Fire (" << fireX << "," << fireY << ")\n";
    std::cout << " Legend: R robot   F fire   o path (dots)   . empty\n\n";

    const int labelW = (roomSize >= 10) ? 3 : 2;

    std::cout << std::setw(labelW) << ' ';
    for (int x = 0; x < roomSize; x++) {
        std::cout << (x % 10) << ' ';
    }
    std::cout << '\n';

    for (int y = 0; y < roomSize; y++) {
        std::cout << std::setw(labelW - 1) << y << ' ';
        for (int x = 0; x < roomSize; x++) {
            char cell = '.';
            const bool onRobot = (x == robotX && y == robotY);
            const bool onFire = (x == fireX && y == fireY);
            const bool wasHere =
                y < static_cast<int>(visited.size()) &&
                x < static_cast<int>(visited[y].size()) && visited[y][x];

            if (onRobot) {
                cell = 'R';
            } else if (onFire) {
                cell = 'F';
            } else if (wasHere) {
                cell = 'o';
            }
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}
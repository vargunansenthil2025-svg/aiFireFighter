#include "pathfinding.h"
#include <cmath>
#include <queue>
#include <algorithm>

// BFS to find shortest path to position one block away from fire
std::vector<std::pair<int, int>> findShortestPath(int startX, int startY, int fireX, int fireY, int roomSize) {
    std::vector<std::vector<std::pair<int, int>>> parent(roomSize, std::vector<std::pair<int, int>>(roomSize, {-1, -1}));
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited_bfs(roomSize, std::vector<bool>(roomSize, false));
    
    q.push({startX, startY});
    visited_bfs[startY][startX] = true;
    
    // Directions: up, down, left, right, and 4 diagonals
    int dx[] = {0, 0, -1, 1, -1, -1, 1, 1};
    int dy[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        // Check if this position is one block away from fire (considering diagonal as adjacent)
        int distX = std::abs(x - fireX);
        int distY = std::abs(y - fireY);
        if ((distX <= 1 && distY <= 1) && !(x == fireX && y == fireY)) {
            // Reconstruct path
            std::vector<std::pair<int, int>> path;
            int cx = x, cy = y;
            while (cx != -1 && cy != -1) {
                path.push_back({cx, cy});
                auto [px, py] = parent[cy][cx];
                cx = px;
                cy = py;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        // Explore neighbors (8 directions including diagonals)
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < roomSize && ny >= 0 && ny < roomSize && !visited_bfs[ny][nx]) {
                visited_bfs[ny][nx] = true;
                parent[ny][nx] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    
    return {}; // No path found (shouldn't happen in valid scenario)
}

static std::vector<std::pair<int, int>> shortestPath;
static size_t pathIndex = 0;

bool moveRobotTowardsFire(int &robotX, int &robotY, int fireX, int fireY,
                          std::vector<std::vector<bool>> &visited) {
    // Mark current position as visited
    visited[robotY][robotX] = true;
    
    // Check if we're adjacent to fire (including diagonally)
    int distX = std::abs(robotX - fireX);
    int distY = std::abs(robotY - fireY);
    if ((distX <= 1 && distY <= 1) && !(robotX == fireX && robotY == fireY)) {
        return true;
    }
    
    // Calculate shortest path if we haven't already
    if (shortestPath.empty()) {
        shortestPath = findShortestPath(robotX, robotY, fireX, fireY, visited.size());
        pathIndex = 1; // Skip starting position
    }
    
    // Follow the shortest path
    if (pathIndex < shortestPath.size()) {
        robotX = shortestPath[pathIndex].first;
        robotY = shortestPath[pathIndex].second;
        pathIndex++;
    }
    
    // Re-check distance after move
    distX = std::abs(robotX - fireX);
    distY = std::abs(robotY - fireY);
    if ((distX <= 1 && distY <= 1) && !(robotX == fireX && robotY == fireY)) {
        return true;
    }
    
    return false; 
}

#include "vision_sim.h"
#include <opencv2/opencv.hpp>

using namespace cv;

void renderSimulation(int roomSize, int robotX, int robotY, int fireX, int fireY) {
    int cellSize = 50; 
    int imgSize = roomSize * cellSize;
    
    Mat img(imgSize, imgSize, CV_8UC3, Scalar(255, 255, 255));

    for (int i = 0; i <= imgSize; i += cellSize) {
        line(img, Point(i, 0), Point(i, imgSize), Scalar(200, 200, 200), 1);
        line(img, Point(0, i), Point(imgSize, i), Scalar(200, 200, 200), 1);
    }

    Point fireCenter((fireX * cellSize) + (cellSize / 2), (fireY * cellSize) + (cellSize / 2));
    circle(img, fireCenter, cellSize / 3, Scalar(0, 0, 255), -1); 

    Point robotCenter((robotX * cellSize) + (cellSize / 2), (robotY * cellSize) + (cellSize / 2));
    circle(img, robotCenter, cellSize / 3, Scalar(255, 0, 0), -1); 

    imshow("AI Fire-Fighting Simulation", img);
    waitKey(1); 
}
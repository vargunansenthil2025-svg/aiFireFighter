#include "iot_logger.h"
#include <iostream>
#include <fstream>
#include <ctime>

void initIoTLogger() {
    std::ofstream logFile("iot_telemetry.txt", std::ios::out | std::ios::trunc);
    if (logFile.is_open()) {
        logFile << "---SMART FIRE ROBOT IOT TELEMETRY LOG---\n"; 
        logFile.close();
    }
}

void logEvent(std::string message) {
    std::ofstream logFile("iot_telemetry.txt", std::ios::app); 
    if (logFile.is_open()) {

        std::time_t now = std::time(nullptr);
        char* dt = std::ctime(&now); 
        std::string timeStr(dt);
        if (!timeStr.empty() && timeStr[timeStr.length()-1] == '\n') {
            timeStr.pop_back(); 
        }
        logFile << "[" << timeStr << "] " << message << "\n";
        logFile.close();
    }
}
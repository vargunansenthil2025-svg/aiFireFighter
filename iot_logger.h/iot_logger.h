#ifndef IOT_LOGGER_H
#define IOT_LOGGER_H

#include <string>

void initToLogger();
void logEvent(std::string message);

#endif

#include "iot_logger.h"
#include <iostream>
#include <fstream>
#include <ctime>

void initIoTLogger(){
  std::ofstream logFile("iot_telemetry.txt",std::ios::out | std::ios::trunc);
  if (logFile.is_open()){
    logfile << "---SMART FIRE ROBOT IOT TELEMETRY LOG---\n"
      logFile.close();
  }
}
void logEvent(std::string message){
  if(logfile.is_open()){
    sid::time_t now = std::time(nullptr);
    char timeBuffer[26];
    ctime_r(&now,timeBuffer);
    std::string timeStr(timeBuffer);
    timeStr.pop_back();

    logFile << "[" << timeStr << "]" << message << "\n";
    logFile.close();
  }
}

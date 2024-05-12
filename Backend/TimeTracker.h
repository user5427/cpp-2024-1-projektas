//
// Created by arnas on 4/28/24.
//

#ifndef CPP_2024_1_PROJEKTAS_TIMETRACKER_H
#define CPP_2024_1_PROJEKTAS_TIMETRACKER_H


#include <string>
#include "Data.h"
#include "../frontend/SimulatedTimeTracker.h"
class TimeTracker : public SimulatedTimeTracker{
private:
    struct TimeTrackerImpl;
    struct TimeTrackerImpl *ptr;
public:
    TimeTracker();
    int addEntry(std::string Name, long long BTime, long long ETime, std::string comment);
    int initFileio(std::string FileName);
    int writeToFile();
    int appendToFile();
    int pause(long long Time);
    int readFromFile();
    int beginEntry(std::string Name, long long BTime, std::string comment);
    int endEntry(long long ETime);
    std::vector<Data> getData();
    bool isThereEventStarted();

    bool isTherePausedEvent();

    std::string activeEventName();

    // Returns the duration of the current event in seconds
    long long getCurrentEventDuration();
};


#endif //CPP_2024_1_PROJEKTAS_TIMETRACKER_H

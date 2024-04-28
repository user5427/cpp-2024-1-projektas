//
// Created by arnas on 4/28/24.
//

#ifndef CPP_2024_1_PROJEKTAS_TIMETRACKER_H
#define CPP_2024_1_PROJEKTAS_TIMETRACKER_H


#include <string>

class TimeTracker {
private:
    struct TimeTrackerImpl;
    struct TimeTrackerImpl *ptr;
public:
    TimeTracker();
    int addEntry(std::string Name, long BTime, long ETime);
    int initFileio(std::string FileName);
    int writeToFile();
    int appendToFile();
    int readFromFile();
    int beginEntry(std::string Name, long BTime);
    int endEntry(long ETime);
    int closeFile();
    int reopenFile();
};


#endif //CPP_2024_1_PROJEKTAS_TIMETRACKER_H

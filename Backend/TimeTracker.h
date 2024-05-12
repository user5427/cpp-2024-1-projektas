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
    int addEntry(std::string Name, long BTime, long ETime, std::string comment);
    int initFileio(std::string FileName);
    int writeToFile();
    int appendToFile();
    int pause(long Time);
    int readFromFile();
    int beginEntry(std::string Name, long BTime, std::string comment);
    int endEntry(long ETime);
    int closeFile();
    int reopenFile();
    std::vector<Data> getData();
    // gal reiktu ir paprasto beginEntry tik su Name parametru? TODO
    // is github "Pagrindinės funkcijos yra startEvent, pauseEvent, stopEvent, comment.", reikia igyvendinti/pervardinti sias funkcijas? TODO
    // reikia galimybes gauti visus galimus veiksmus TODO
    // dar reikia igyvendinti visus reikalavimus is pdf failo TODO
    // is SimulatedTimeTracker igyvendinti metodus TODO
    // std::chrono::system_clock::time_point begin; TODO long labai nepatogus
    bool isThereEventStarted();

    bool isTherePausedEvent();

    std::string activeEventName();

    // Returns the duration of the current event in seconds
    long getCurrentEventDuration();
};


#endif //CPP_2024_1_PROJEKTAS_TIMETRACKER_H

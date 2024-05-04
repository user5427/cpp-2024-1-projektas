//
// Created by arnas on 4/28/24.
//

#ifndef CPP_2024_1_PROJEKTAS_TIMETRACKER_H
#define CPP_2024_1_PROJEKTAS_TIMETRACKER_H


#include <string>
#include "Data.h"

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
    std::vector<Data> getData();
    // gal reiktu ir paprasto beginEntry tik su Name parametru? TODO
    // is github "Pagrindinės funkcijos yra startEvent, pauseEvent, stopEvent, comment.", reikia igyvendinti/pervardinti sias funkcijas? TODO
    // reikia galimybes gauti visus galimus veiksmus TODO
    // reikia galimybes gauti visus ivykius pagal veiksma TODO
    // ai ir nesikompiliuos nes cmakelist.txt isemiau is kompiliavimo saraso
    // dar reikia igyvendinti visus reikalavimus is pdf failo TODO
    // is SimulatedTimeTracker igyvendinti metodus TODO
};


#endif //CPP_2024_1_PROJEKTAS_TIMETRACKER_H

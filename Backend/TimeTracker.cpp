//
// Created by arnas on 4/28/24.
//

#include <vector>
#include "TimeTracker.h"
#include "Data.h"
#include "FileIO.h"

struct TimeTracker::TimeTrackerImpl{
    TimeTrackerImpl() : file(""){

    }
    bool currentlyTracking = false;
    std::string Name;
    bool openedFile = false;
    long begin = 0;
    FileIO file ;
    long end = 0;
    void writeToVector(){
        Data d(Name, begin, end);
        data.push_back(d);
        currentlyTracking = false;
    }
    std::vector<Data> data;
};

TimeTracker::TimeTracker() {
    ptr = new struct TimeTrackerImpl;
}

int TimeTracker::addEntry(std::string Name, long BTime, long ETime) {
    if(ptr->currentlyTracking){
        return 0;
    }
    ptr->Name = Name;
    ptr->begin = BTime;
    ptr->end = ETime;
    ptr->writeToVector();
}

int TimeTracker::initFileio(std::string fileName) {
    ptr -> file = FileIO(fileName);
    ptr->openedFile = true;
}

int TimeTracker::writeToFile() {
    if(!ptr->openedFile)
        return 0;
    std::vector<std::string> Raw;
    for(Data d : ptr->data){
        Raw.push_back(d.Name +", " + std::to_string(d.beginT) + ", " + std::to_string(d.endT) +"\n");
    }
    ptr->file.write(Raw);
    return 1;
}

int TimeTracker::appendToFile() {
    if(readFromFile() == 0){
        return 0;
    }
    if(writeToFile() == 0){
        return 0;
    }
    return 1;
}

int TimeTracker::readFromFile() {
    std::vector<std::string> Raw = ptr->file.readAll();
    if(Raw.empty() || ptr->currentlyTracking){
        return 0;
    }
    std::string Delim = ", ";
    for(std::string ENT : Raw){
        std::string Name = ENT.substr(0, ENT.find(Delim));
        ENT.erase(0, ENT.find(Delim) + Delim.length());
        std::string Begin = ENT.substr(0, ENT.find(Delim));
        ENT.erase(0, ENT.find(Delim) + Delim.length());
        std::string End = ENT;
        ptr->begin = std::stol(Begin);
        ptr->end = std::stol(End);
        ptr->Name = Name;
        ptr->writeToVector();
    }
    return 1;
}

int TimeTracker::beginEntry(std::string Name, long BTime) {
    if(ptr->currentlyTracking)
        return 0;
    ptr->Name = Name;
    ptr->begin = BTime;
    return 1;
}

int TimeTracker::endEntry(long ETime) {
    if(!ptr->currentlyTracking)
        return 0;
    ptr->end = ETime;
    ptr->writeToVector();
    return 1;
}

int TimeTracker::closeFile() {
    if(ptr->openedFile){
        ptr->file.close();
        return 1;
    }
    return 0;
}

int TimeTracker::reopenFile() {
    if(!ptr->openedFile){
        return 0;
    }
    ptr->file.open();
    return 1;
}

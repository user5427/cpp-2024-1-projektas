//
// Created by arnas on 4/28/24.
//

#include <vector>
#include <ctime>
#include "TimeTracker.h"
#include "Data.h"
#include "FileIO.h"
#include "SimulatedTimeTracker.h"


struct TimeTracker::TimeTrackerImpl{
    TimeTrackerImpl() : file(""){

    }
    int isPaused = 0;
    std::string pausedName;
    std::string pausedComment;
    bool currentlyTracking = false;
    std::string Name, Comment;
    bool openedFile = false;
    long long begin = 0;
    FileIO file ;
    long long end = 0;
    void writeToVector(){
        Data d(Name, begin, end, Comment);
        data.push_back(d);
        if(!isPaused)
            currentlyTracking = false;
    }
    std::vector<Data> data;
};

/*
 * bool isThereEventStarted(){
        return false;
    }

    bool isTherePausedEvent(){
        return false;
    }

    std::string activeEventName(){
        return "activeEvent";
    }

    // Returns the duration of the current event in seconds
    long getCurrentEventDuration() {
        return 485181;
    }
 */
TimeTracker::TimeTracker() {
    ptr = new struct TimeTrackerImpl;
}

int TimeTracker::addEntry(std::string Name, long long BTime, long long ETime, std::string Comment) {
    if(ptr->currentlyTracking){
        return 0;
    }
    ptr->Comment = Comment;
    ptr->Name = Name;
    ptr->begin = BTime;
    ptr->end = ETime;
    ptr->writeToVector();
    return 1;
}

int TimeTracker::initFileio(std::string fileName) {
    std::string ftype = ".csv";
    if(fileName.compare(fileName.size() - ftype.size(), ftype.size(), ftype)!=0){
        return 0;
    }
    ptr -> file = FileIO(fileName);
    ptr->openedFile = true;
    return 1;
}

int TimeTracker::writeToFile() {
    if(!ptr->openedFile)
        return 0;
    std::vector<std::string> Raw;
    for(Data d : ptr->data){
        Raw.push_back(d.Name +", " + std::to_string(d.beginT) + ", " + std::to_string(d.endT) + ", " + d.comment + "\n");
    }
    ptr->file.write(Raw);
    return 1;
}

int TimeTracker::appendToFile() {
    readFromFile();

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
        std::string End = ENT.substr(0, ENT.find(Delim));
        ENT.erase(0, ENT.find(Delim) + Delim.length());
        std::string com = ENT.substr(0, ENT.find("\n"));
        ptr->begin = std::stol(Begin);
        ptr->end = std::stol(End);
        ptr->Name = Name;
        ptr->Comment = com;
        ptr->writeToVector();
    }
    return 1;
}

int TimeTracker::beginEntry(std::string Name, long long BTime, std::string comment) {
    if(!ptr->isPaused&&ptr->currentlyTracking)
        return 0;
    ptr->Name = Name;
    ptr->begin = BTime;
    ptr->Comment = comment;
    ptr->currentlyTracking = 1;
    return 1;
}

int TimeTracker::endEntry(long long ETime) {
    if(!ptr->currentlyTracking)
        return 0;
    ptr->end = ETime;
    ptr->writeToVector();
    return 1;
}


std::vector<Data> TimeTracker::getData() {
    return ptr->data;
}

bool TimeTracker::isThereEventStarted() {
    return ptr->currentlyTracking;
}

long long TimeTracker::getCurrentEventDuration() {
    if(ptr->end == 0) {
        return (time(0) - ptr->begin) / 1000;
    } else{
        return (ptr->end - ptr->begin)/1000;
    }
}

bool TimeTracker::isTherePausedEvent() {
    return ptr->isPaused;
}

std::string TimeTracker::activeEventName() {
    return ptr->Name;
}

int TimeTracker::pause(long long T) {
    if(!ptr->currentlyTracking){
        return 0;
    }
    if(!ptr->isPaused) {
        ptr->pausedComment = ptr->Comment;
        ptr->pausedName = ptr->Name;
        ptr->isPaused = 1;
        endEntry(T);
    } else{
        beginEntry(ptr->pausedName, T, ptr->Comment);
        ptr->Name = ptr->pausedName;
        ptr->Comment = ptr->pausedComment;
        ptr->isPaused = 0;
    }
    return 1;
}

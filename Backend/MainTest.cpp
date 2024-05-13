//
// Created by arnas on 5/12/24.
//

#include "TimeTracker.h"
#include <iostream>

void pr(){
    std::cout<<"T\n";
}

int main(){
    TimeTracker tt;
    tt.beginEntry("TestName1", 0, "TestComment1");
    std::cout<<tt.isThereEventStarted()<<"  "<<tt.getCurrentEventDuration()<<std::endl;
    tt.endEntry(1);
    std::cout<<tt.isThereEventStarted()<<" "<<tt.isTherePausedEvent()<<" "<<tt.activeEventName()<<std::endl;
    tt.beginEntry("TestName2", 10, "TestComment2");
    tt.pause(12);
    tt.pause(17);
    tt.endEntry(20);
    tt.initFileio("TEST.csv");
    tt.writeToFile();
    TimeTracker tt2;
    tt2.initFileio("TEST2.csv");
    tt2.readFromFile();
    tt2.addEntry("TestName3", 100, 200, "Comment3");
    tt2.writeToFile();
    TimeTracker tt3;
    tt3.initFileio("TEST3.csv");
    tt3.addEntry("T4", 1000, 1500, "C4");
    tt3.appendToFile();
    tt3.getData().clear();
    tt3.addEntry("T4", 2000, 2500, "C5");
    tt3.appendToFile();
    return 1;
}
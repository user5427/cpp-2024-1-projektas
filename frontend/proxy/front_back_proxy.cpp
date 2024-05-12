//
// Created by topto on 2024-05-12.
//

#include "front_back_proxy.h"
#include "../backend_singleton/TimeTracker_Singleton.h"

void front_back_proxy::beginEntry(std::string name, std::chrono::time_point<std::chrono::system_clock> time, std::string comment) {
    TimeTracker_Singleton::getTracker()->beginEntry(name, time, comment);
}

void front_back_proxy::endEntry(std::chrono::time_point<std::chrono::system_clock> time) {
    TimeTracker_Singleton::getTracker()->endEntry(time);
}

void front_back_proxy::pauseEntry(std::chrono::time_point<std::chrono::system_clock> time) {
    TimeTracker_Singleton::getTracker()->pause(time);
}

bool front_back_proxy::isEntryActive() {
    return TimeTracker_Singleton::getTracker()->isThereEventStarted();
}

long long front_back_proxy::getActiveEntryTime() {
    return TimeTracker_Singleton::getTracker()->getCurrentEventDuration();
}

std::string front_back_proxy::getActiveEntryName() {
    return TimeTracker_Singleton::getTracker()->activeEventName();
}
//
// Created by topto on 2024-05-12.
//

#include "front_back_proxy.h"
#include "../backend_singleton/TimeTracker_Singleton.h"
#include "../longToChrono/longConverter.h"
#include "../error_singleton/Error_Singleton.h"

void front_back_proxy::beginEntry(std::string name, std::chrono::time_point<std::chrono::system_clock> time, std::string comment) {
    Error_Singleton::clearError();
    if (name.empty()) {
        Error_Singleton::setError("Event cannot be empty");
        return;
    }

    long long timeC = longConverter::convertToLong(time);
    TimeTracker_Singleton::getTracker()->beginEntry(name, timeC, comment);
}

void front_back_proxy::endEntry(std::chrono::time_point<std::chrono::system_clock> time) {
//    Error_Singleton::clearError();
    long long timeC = longConverter::convertToLong(time);
    TimeTracker_Singleton::getTracker()->endEntry(timeC);
}

void front_back_proxy::pauseEntry(std::chrono::time_point<std::chrono::system_clock> time) {
//    Error_Singleton::clearError();
    long long timeC = longConverter::convertToLong(time);
    TimeTracker_Singleton::getTracker()->pause(timeC);
}

bool front_back_proxy::isEntryActive() {
//    Error_Singleton::clearError();
    return TimeTracker_Singleton::getTracker()->isThereEventStarted();
}

long long front_back_proxy::getActiveEntryTime() {
//    Error_Singleton::clearError();
    return TimeTracker_Singleton::getTracker()->getCurrentEventDuration();
}

std::string front_back_proxy::getActiveEntryName() {
    Error_Singleton::clearError();
    return TimeTracker_Singleton::getTracker()->activeEventName();
}

void front_back_proxy::initFile(std::string path) {
    Error_Singleton::clearError();
    try {
        int err = TimeTracker_Singleton::getTracker()->initFileio(path);
        if (err == 0) {
            Error_Singleton::setError("Error initializing file");
        }
    } catch (std::exception &e) {
        Error_Singleton::setError("Exception initializing file");
        Error_Singleton::setException(true);
        return;
    }

}

void front_back_proxy::saveToFile() {
    try {
        Error_Singleton::clearError();
        int err = TimeTracker_Singleton::getTracker()->writeToFile();
        if (err == 0) {
            Error_Singleton::setError("Error writing to file");
        }
    } catch (std::exception &e) {
        Error_Singleton::setError("Exception writing to file");
        Error_Singleton::setException(true);
        return;
    }
}

void front_back_proxy::loadFromFile() {
    try {
        Error_Singleton::clearError();
        int err = TimeTracker_Singleton::getTracker()->readFromFile();
        if (err == 0) {
            Error_Singleton::setError("Error reading from file");
        }
    } catch (std::exception &e) {
        Error_Singleton::setError("Exception reading from file");
        Error_Singleton::setException(true);
        return;
    }
}

bool front_back_proxy::isEntryPaused() {
//    Error_Singleton::clearError();
    return TimeTracker_Singleton::getTracker()->isTherePausedEvent();
}

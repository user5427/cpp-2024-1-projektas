//
// Created by topto on 2024-05-12.
//

#include "TimeTracker_Singleton.h"

TimeTracker* TimeTracker_Singleton::pTracker = nullptr;

TimeTracker *TimeTracker_Singleton::getTracker() {
    if (pTracker == nullptr) {
        pTracker = new TimeTracker();
    }
    return pTracker;
}

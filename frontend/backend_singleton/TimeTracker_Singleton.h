//
// Created by topto on 2024-05-12.
//

#ifndef CPP_2024_1_PROJEKTAS_TIMETRACKER_SINGLETON_H
#define CPP_2024_1_PROJEKTAS_TIMETRACKER_SINGLETON_H


#include "../../backend/TimeTracker.h"

class TimeTracker_Singleton {
public:
    static TimeTracker *getTracker();

private:
    static TimeTracker *pTracker;
};


TimeTracker* TimeTracker_Singleton::pTracker = nullptr;

TimeTracker *TimeTracker_Singleton::getTracker() {
    if (pTracker == nullptr) {
        pTracker = new TimeTracker();
    }
    return pTracker;
}

#endif //CPP_2024_1_PROJEKTAS_TIMETRACKER_SINGLETON_H

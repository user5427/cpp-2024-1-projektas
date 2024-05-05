//
// Created by topto on 2024-05-05.
//

#include "dataPoint.h"

struct dataPoint::dataPointImpl {
    std::string eventName;
    std::string eventComment;
    std::chrono::system_clock::time_point begin;
    std::chrono::system_clock::time_point end;
    std::string duration;

    dataPointImpl(std::string eventM, std::chrono::system_clock::time_point begin,
                  std::chrono::system_clock::time_point end, std::string comment) : eventName(eventM), begin(begin),
                                                                                    end(end),
                                                                                    eventComment(comment) {};

    std::string getEventName() {
        return eventName;
    }

    std::string getEventDate() {
        std::time_t time = std::chrono::system_clock::to_time_t(begin);
        std::tm *localTime = std::localtime(&time);

        std::string formatedDate = "";
        formatedDate += std::to_string(localTime->tm_year + 1900) + "-";
        if (localTime->tm_mon < 10) {
            formatedDate += "0";
        }
        formatedDate += std::to_string(localTime->tm_mon) + "-";
        if (localTime->tm_mday < 10) {
            formatedDate += "0";
        }
        formatedDate += std::to_string(localTime->tm_mday);
        return formatedDate;
    }

    std::string getEventTime() {
        std::time_t time = std::chrono::system_clock::to_time_t(begin);
        std::tm *localTime = std::localtime(&time);

        std::string timeStr = "";

        if (localTime->tm_hour < 10) {
            timeStr += "0";
        }
        timeStr += std::to_string(localTime->tm_hour) + ":";
        if (localTime->tm_min < 10) {
            timeStr += "0";
        }
        timeStr += std::to_string(localTime->tm_min) + ":";
        if (localTime->tm_sec < 10) {
            timeStr += "0";
        }
        timeStr += std::to_string(localTime->tm_sec);
        return timeStr;
    }

    std::string getEventComment() {
        return eventComment;
    }

    std::string getDuration() {
        std::chrono::duration<double> duration = end - begin;
        int hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
        int minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();// % 60;
        int seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();// % 60;

        std::string durationStr = "";
        if (hours < 10) {
            durationStr += "0";
        }
        durationStr += std::to_string(hours) + ":";
        if (minutes < 10) {
            durationStr += "0";
        }
        durationStr += std::to_string(minutes) + ":";
        if (seconds < 10) {
            durationStr += "0";
        }
        durationStr += std::to_string(seconds);
        return durationStr;
    }
};

dataPoint::dataPoint(std::string eventName, std::chrono::system_clock::time_point begin,
                     std::chrono::system_clock::time_point end, std::string comment) : pimpl(
        new dataPointImpl(std::move(eventName), begin, end, std::move(comment))) {}

dataPoint::~dataPoint() {
    delete pimpl;
}

std::string dataPoint::getEventName() {
    return pimpl->getEventName();
}

std::string dataPoint::getEventDate() {
    return pimpl->getEventDate();
}

std::string dataPoint::getEventTime() {
    return pimpl->getEventTime();
}

std::string dataPoint::getEventComment() {
    return pimpl->getEventComment();
}

std::string dataPoint::getDuration() {
    return pimpl->getDuration();
}

dataPoint::dataPoint(const dataPoint &other) {
    pimpl = new dataPointImpl(other.pimpl->eventName, other.pimpl->begin, other.pimpl->end, other.pimpl->eventComment);
}


// Path: frontend/dataPoint.cpp

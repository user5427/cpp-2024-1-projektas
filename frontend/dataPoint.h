//
// Created by topto on 2024-05-05.
//

#ifndef CPP_2024_1_PROJEKTAS_DATAPOINT_H
#define CPP_2024_1_PROJEKTAS_DATAPOINT_H


#include <string>
#include <chrono>

class dataPoint {
public:
    dataPoint(std::string eventName, std::chrono::system_clock::time_point begin, std::chrono::system_clock::time_point end, std::string comment);
    dataPoint() = default;
    //copy constructor
    dataPoint(const dataPoint &other);
    ~dataPoint();
    std::string getEventName();
    std::string getEventDate();
    std::string getEventTime();
    std::string getEventComment();
    std::string getDuration();
private:
    struct dataPointImpl;
    dataPointImpl *pimpl;
};


#endif //CPP_2024_1_PROJEKTAS_DATAPOINT_H

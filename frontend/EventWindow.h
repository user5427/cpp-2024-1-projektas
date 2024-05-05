//
// Created by topto on 2024-05-05.
//

#ifndef CPP_2024_1_PROJEKTAS_EVENTWINDOW_H
#define CPP_2024_1_PROJEKTAS_EVENTWINDOW_H


#include <vector>
#include "dataPoint.h"

class EventWindow {
public:
    EventWindow();
    ~EventWindow();
    bool isOpen();
    void close();
    void open();
    void setData(std::vector<dataPoint> data);

private:
    struct EventWindowImpl;
    EventWindowImpl *pimpl;
};


#endif //CPP_2024_1_PROJEKTAS_EVENTWINDOW_H

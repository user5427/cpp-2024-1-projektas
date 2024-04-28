//
// Created by arnas on 4/28/24.
//

#ifndef CPP_2024_1_PROJEKTAS_DATA_H
#define CPP_2024_1_PROJEKTAS_DATA_H


#include <string>

class Data {
public:
    std::string Name;
    long beginT, endT;
    Data(std::string Name, long bTime, long eTime);
};


#endif //CPP_2024_1_PROJEKTAS_DATA_H

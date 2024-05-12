//
// Created by topto on 2024-05-12.
//

#ifndef CPP_2024_1_PROJEKTAS_LONGCONVERTER_H
#define CPP_2024_1_PROJEKTAS_LONGCONVERTER_H


#include <chrono>

class longConverter {
    // convert to chrono and vise versa
public:
    static long long convertToLong(std::chrono::time_point<std::chrono::system_clock> time);
    static std::chrono::time_point<std::chrono::system_clock> convertToChrono(long long time);
};


#endif //CPP_2024_1_PROJEKTAS_LONGCONVERTER_H

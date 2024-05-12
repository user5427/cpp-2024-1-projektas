//
// Created by topto on 2024-05-12.
//

#include "longConverter.h"

long long longConverter::convertToLong(std::chrono::time_point<std::chrono::system_clock> time) {
    return std::chrono::system_clock::to_time_t(time);
}

std::chrono::time_point<std::chrono::system_clock> longConverter::convertToChrono(long long time) {
    return std::chrono::system_clock::from_time_t(time);
}

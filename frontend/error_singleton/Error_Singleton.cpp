//
// Created by topto on 2024-05-12.
//

#include "Error_Singleton.h"
std::string Error_Singleton::error = "";
bool Error_Singleton::errorFlag = false;
bool Error_Singleton::exceptionFlag = false;

std::string Error_Singleton::getError() {
    return error;
}

void Error_Singleton::setError(std::string error) {
    Error_Singleton::error = error;
    Error_Singleton::errorFlag = true;
}

bool Error_Singleton::hasError() {
    return errorFlag;
}

void Error_Singleton::clearError() {
    error = "";
    errorFlag = false;
    exceptionFlag = false;
}

bool Error_Singleton::hasException() {
    return exceptionFlag;
}

void Error_Singleton::setException(bool flag) {
    exceptionFlag = flag;
}

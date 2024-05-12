//
// Created by topto on 2024-05-12.
//

#ifndef CPP_2024_1_PROJEKTAS_ERROR_SINGLETON_H
#define CPP_2024_1_PROJEKTAS_ERROR_SINGLETON_H


#include <string>

class Error_Singleton {
public:
    static std::string getError();
    static void setError(std::string error);
    static bool hasError();
    static void clearError();
private:
    static std::string error;
    static bool errorFlag;
};

std::string Error_Singleton::error = "";
bool Error_Singleton::errorFlag = false;

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
}


#endif //CPP_2024_1_PROJEKTAS_ERROR_SINGLETON_H

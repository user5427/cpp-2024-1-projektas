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
    static bool hasException();
    static void setException(bool flag);
    static void clearError();
private:
    static std::string error;
    static bool errorFlag;
    static bool exceptionFlag;
};




#endif //CPP_2024_1_PROJEKTAS_ERROR_SINGLETON_H

//
// Created by arnas on 4/28/24.
//

#ifndef CPP_2024_1_PROJEKTAS_FILEIO_H
#define CPP_2024_1_PROJEKTAS_FILEIO_H


#include <string>
#include <vector>

class FileIO {
private:
    ///pimpl
    struct FileIOImpl;
    struct FileIOImpl *ptr;
public:
    FileIO(std::string fileName);
    ///Get All Contents of the Data File
    std::vector<std::string> readAll();
    int write(std::vector<std::string> data);
};


#endif //CPP_2024_1_PROJEKTAS_FILEIO_H

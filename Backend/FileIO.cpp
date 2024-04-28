//
// Created by arnas on 4/28/24.
//

#include <fstream>
#include "FileIO.h"

struct FileIO::FileIOImpl{
    std::string Name;
    std::fstream File;
};

FileIO::FileIO(std::string fileName) {
    ptr = new struct FileIOImpl;
    ptr->Name = fileName;
    ptr->File.open(fileName, std::ios::in | std::ios::out);
}

void FileIO::close() {
    ptr->File.close();
}

int FileIO::open() {
    ptr->File.open(ptr->Name, std::ios::in | std::ios::out);
    return ptr->File.is_open();
}


std::vector<std::string> FileIO::readAll() {
    std::vector<std::string> data;
    while(!ptr->File.eof()) {
        char TMP[50001];
        ptr->File.getline(TMP, 50000);
        std::string inf(TMP);
        data.push_back(inf);
    }
    return data;
}

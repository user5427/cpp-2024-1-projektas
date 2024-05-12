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
    //ptr->File.open(fileName, std::ios::in | std::ios::out | std::ios::trunc);
}


std::vector<std::string> FileIO::readAll() {
    std::vector<std::string> data;
    std::string inf;
    ptr->File.open(ptr->Name, std::fstream::in);
    while(std::getline(ptr->File, inf)) {
        char TMP[50001];
        //ptr->File.getline(TMP, 50000);


        //std::string inf(TMP);
        data.push_back(inf);
    }
    ptr->File.close();
    return data;
}

int FileIO::write(std::vector<std::string> data) {
    ptr->File.open(ptr->Name, std::fstream::out);
    for(std::string R : data){
        ptr->File<<R;
    }
    ptr->File.close();
    return 1;
}

//
// Created by arnas on 4/28/24.
//

#include "Data.h"

Data::Data(std::string Name, long long bTime, long long eTime, std::string Comment) {
    this->Name = Name;
    beginT = bTime;
    endT = eTime;
    comment = Comment;
}

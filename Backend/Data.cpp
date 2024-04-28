//
// Created by arnas on 4/28/24.
//

#include "Data.h"

Data::Data(std::string Name, long bTime, long eTime) {
    this->Name = Name;
    beginT = bTime;
    endT = eTime;
}

cmake_minimum_required(VERSION 3.27)
project(cpp_2024_1_projektas)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_2024_1_projektas main.cpp
#        Backend/FileIO.cpp
#        Backend/FileIO.h
#        Backend/FileIO.cpp
#        Backend/TimeTracker.cpp
#        Backend/TimeTracker.h
#        Backend/Data.cpp
#        Backend/Data.h
        frontend/MyWindow.cpp
        frontend/MyWindow.h
        frontend/Button.cpp
        frontend/Button.h
        frontend/DropBox.cpp
        frontend/DropBox.h
        frontend/Slider.cpp
        frontend/Slider.h
        frontend/CommentBox.cpp
        frontend/CommentBox.h
        frontend/AbstractUIElement.h
        frontend/SimulatedTimeTracker.h
        frontend/Clock.cpp
        frontend/Clock.h)

include_directories(headers /usr/include c:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cpp_2024_1_projektas ${SFML_LIBRARIES})
endif()

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# copy dlls to build directory
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
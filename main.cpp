#include <iostream>
#include <chrono>
#include <list>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "frontend/MyWindow.h"
#include "frontend/SimulatedTimeTracker.h"
#include "frontend/backend_singleton/TimeTracker_Singleton.h"
#include "frontend/proxy/front_back_proxy.h"

int main() {
    // check if there is a file db.txt
    front_back_proxy::initFile("db.csv");
    front_back_proxy::loadFromFile();
    SimulatedTimeTracker *timeTracker = new SimulatedTimeTracker();
    MyWindow *window = new MyWindow(timeTracker);
    while (window->getRenderWindow()->isOpen()) {
        window->update();
        window->draw();
    }
    front_back_proxy::saveToFile();
    delete window;
    return 0;
}

//    sf::Clock clock;
// Create a list to store the start and end times
//    std::list<std::chrono::high_resolution_clock::time_point> times;
//
//    // Read if the user inputed start stop or pause in the console
//    std::string input;
//    bool work = true;
//    while (work){
//        std::cin >> input;
//        if (input == "start") {
//            times.push_back(std::chrono::high_resolution_clock::now());
//            std::cout << "Starting the event" << std::endl;
//        } else if (input == "stop") {
//            times.push_back(std::chrono::high_resolution_clock::now());
//            std::cout << "Stopping the event" << std::endl;
//            work = false;
//        } else if (input == "pause") {
//            times.push_back(std::chrono::high_resolution_clock::now());
//            std::cout << "Pausing the event" << std::endl;
//        } else {
//            std::cout << "Invalid input" << std::endl;
//        }
//        input = "";
//    }
//
//
//    // Initialize the sum of durations
//    std::chrono::milliseconds sum(0);
//
//    // Iterate over the list of times
//    for (auto it = times.begin(); it != times.end(); ++it) {
//        // Get the start time
//        auto start = *it;
//
//        // If there is a stop time, get it and calculate the duration
//        if (++it != times.end()) {
//            auto stop = *it;
//            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
//
//            // Add the duration to the sum
//            sum += duration;
//        }
//    }
//
//    // Print the total duration
//    std::cout << "The total duration is " << sum.count() << " milliseconds." << std::endl;
//

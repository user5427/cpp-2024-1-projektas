#include <iostream>
#include <chrono>
#include <list>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "frontend/MyWindow.h"
#include "frontend/SimulatedTimeTracker.h"

int main() {
    sf::Clock clock;
    int updatesPerSecond = 60;
    long long int timeSinceLastUpdate = 0;
    long long int timePerUpdate = 1000000 / updatesPerSecond;
    SimulatedTimeTracker *timeTracker = new SimulatedTimeTracker();
    MyWindow *window = new MyWindow(timeTracker);
    while (window->getRenderWindow()->isOpen()){
        if (clock.getElapsedTime().asMicroseconds() - timeSinceLastUpdate > timePerUpdate){
            timeSinceLastUpdate += timePerUpdate;
            window->update();
            window->draw();
        }
    }

    delete window;

    return 0;
}


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

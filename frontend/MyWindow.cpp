//
// Created by topto on 2024-05-02.
//

#include <iostream>
#include <filesystem>
#include "MyWindow.h"
#include "Button.h"
#include "DropBox.h"
#include "SimulatedTimeTracker.h"
#include "Clock.h"

struct MyWindow::WindowImpl {
    sf::RenderWindow *renderWindow;
    sf::Texture windowTexture;

    Button *startButton;
    Button *pauseButton;
    Button *stopButton;

    DropBox *dropBox;

    sf::Texture eventDiplsayTexture;
    Clock *clock;
    sf::Texture timeAndDateTexture;

    SimulatedTimeTracker *simulatedTimeTracker = new SimulatedTimeTracker();

    // get date from system
    time_t now = time(0);
    tm *ltm = localtime(&now);

    WindowImpl(SimulatedTimeTracker *pTracker) {
        simulatedTimeTracker = pTracker;
        renderWindow = new sf::RenderWindow(sf::VideoMode(863, 502), "PSP tracker");
        if (!windowTexture.loadFromFile("res/initialPage.png")) {
            std::cout << "Could not load page windowTexture" << std::endl;
            throw std::runtime_error("Could not load page windowTexture");
        }


        startButton = new Button("res/startInactive.png", "res/startHighlight.png", "res/start.png",
                                 "res/pressedStart.png", 556, 425);
        pauseButton = new Button("res/pauseInactive.png", "res/pauseHighlight.png", "res/pauseActive.png",
                                 "res/pressedPause.png", 614, 425);
        stopButton = new Button("res/stopInactive.png", "res/stopHighlight.png", "res/stop.png", "res/pressedStop.png",
                                672, 425);
        dropBox = new DropBox(33, 115, "Events:");
        dropBox->setItems(simulatedTimeTracker->getActionList()); //TODO

        eventDiplsayTexture.loadFromFile("res/eventDisplayBox.png");
        clock = new Clock(473, 26);
        timeAndDateTexture.loadFromFile("res/timeAndDateDisplay.png");
    }

    ~WindowImpl() {
        delete renderWindow;
    }

    void draw() {
        renderWindow->clear();
        sf::Sprite image;
        image.setTexture(windowTexture);
        image.setPosition(0, 0);
        renderWindow->draw(image);
        dropBox->draw(*renderWindow);
        startButton->draw(*renderWindow);
        pauseButton->draw(*renderWindow);
        stopButton->draw(*renderWindow);

        sf::Sprite eventDisplay;
        eventDisplay.setTexture(eventDiplsayTexture);
        eventDisplay.setPosition(463, 374);
        renderWindow->draw(eventDisplay);

        sf::Font font;
        font.loadFromFile("res/fonts/inter/Inter-Regular.ttf");
        std::string eventString;
        if (simulatedTimeTracker->isThereEventStarted()) {
            eventString = simulatedTimeTracker->activeEventName();
        } else {
            eventString = "No events active.";
        }
        sf::Text text(eventString, font, 19);
        sf::Color color(107, 105, 130);
        if (!simulatedTimeTracker->isThereEventStarted())
            text.setFillColor(color);
        text.setPosition(474, 383);
        renderWindow->draw(text);


        sf::Sprite timeAndDate;
        timeAndDate.setTexture(timeAndDateTexture);
        timeAndDate.setPosition(38, 39);
        renderWindow->draw(timeAndDate);
        std::string date = std::to_string(1900 + ltm->tm_year) + "-" ;//+ std::to_string(1 + ltm->tm_mon) + "-" +
                           //std::to_string(ltm->tm_mday);
        if (1 + ltm->tm_mon < 10){
            date += "0";
        }
        date += std::to_string(1 + ltm->tm_mon) + "-";
        if (ltm->tm_mday < 10){
            date += "0";
        }
        date += std::to_string(ltm->tm_mday);

        std::string time;
        if (ltm->tm_hour < 10) {
            time += "0";
        }
        time += std::to_string(ltm->tm_hour) + " : ";
        if (ltm->tm_min < 10) {
            time += "0";
        }
        time += std::to_string(ltm->tm_min) + " : ";
        if (ltm->tm_sec < 10) {
            time += "0";
        }
        time += std::to_string(ltm->tm_sec);

        // gray color
        sf::Color gray(159, 159, 159);

        sf::Text dateText(date, font, 19);
        dateText.setPosition(134, 40);
        dateText.setFillColor(gray);

        sf::Text timeText(time, font, 19);
        timeText.setPosition(134, 68);
        timeText.setFillColor(gray);

        renderWindow->draw(dateText);
        renderWindow->draw(timeText);

        clock->draw(*renderWindow);

        renderWindow->display();
    }

    void update() {
        now = time(0);
        ltm = localtime(&now);
        if (simulatedTimeTracker->isThereEventStarted()) {
            startButton->disable(true);
            pauseButton->disable(false);
            if (simulatedTimeTracker->isTherePausedEvent()) {
                stopButton->disable(true);
            } else {
                stopButton->disable(false);
            }
        } else {
            startButton->disable(false);
            pauseButton->disable(true);
            stopButton->disable(true);
        }

        dropBox->update(*renderWindow);
        startButton->update(*renderWindow);
        pauseButton->update(*renderWindow);
        stopButton->update(*renderWindow);

        long time;
        if (simulatedTimeTracker->isThereEventStarted())
            time = simulatedTimeTracker->getSimulatedTime();
        else {
            time = ltm->tm_hour * 3600 + ltm->tm_min * 60 + ltm->tm_sec;
        }
        clock->update(*renderWindow, time);
        sf::Event event;
        while (renderWindow->pollEvent(event)) {
            handleEvents(event);
        }
    }

    void handleEvents(sf::Event event) {
        if (event.type == sf::Event::EventType::Closed) {
            renderWindow->close();
        } else {
            dropBox->handleEvents(*renderWindow, event);
            startButton->handleEvents(*renderWindow, event);
            pauseButton->handleEvents(*renderWindow, event);
            stopButton->handleEvents(*renderWindow, event);
            clock->handleEvents(*renderWindow, event);
        }
    }

    sf::RenderWindow *getRenderWindow() {
        return renderWindow;
    }


};

MyWindow::MyWindow(SimulatedTimeTracker *pTracker) : ptr(new WindowImpl(pTracker)) {
}

MyWindow::~MyWindow() {
    delete ptr;
}

void MyWindow::draw() {
    ptr->draw();
}

void MyWindow::update() {
    ptr->update();
}

sf::RenderWindow *MyWindow::getRenderWindow() {
    return ptr->getRenderWindow();
}


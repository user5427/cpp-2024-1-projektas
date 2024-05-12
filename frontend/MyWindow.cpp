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
#include "../res/logo.c"
#include "Transparent.h"
#include "WindowBar.h"
#include "EventWindow.h"

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

    WindowBar *windowBar;
    Button *eventButton;

    EventWindow *eventWindow = nullptr;

    WindowImpl(SimulatedTimeTracker *pTracker) {
        simulatedTimeTracker = pTracker;
        renderWindow = new sf::RenderWindow(sf::VideoMode(863, 530), "PSP tracker", sf::Style::None);
        renderWindow->setIcon(gimp_image.width, gimp_image.height, gimp_image.pixel_data);
        renderWindow->setFramerateLimit(60);



        sf::Image backgroundImage;
        if (!windowTexture.loadFromFile("res/initialPage.png") || !backgroundImage.loadFromFile("res/initialPage.png")) {
            std::cout << "Could not load page windowTexture" << std::endl;
            throw std::runtime_error("Could not load page windowTexture");
        }


        bool setShapeS = setShape(renderWindow->getSystemHandle(), backgroundImage);//FIXME OS specific
        bool setTransparencyS = setTransparency(renderWindow->getSystemHandle(), 255);//FIXME OS specific

        startButton = new Button("res/startInactive.png", "res/startHighlight.png", "res/start.png",
                                 "res/pressedStart.png", 556, 425+28);
        pauseButton = new Button("res/pauseInactive.png", "res/pauseHighlight.png", "res/pauseActive.png",
                                 "res/pressedPause.png", 614, 425+28);
        stopButton = new Button("res/stopInactive.png", "res/stopHighlight.png", "res/stop.png", "res/pressedStop.png",
                                672, 425+28);
        dropBox = new DropBox(33, 115+28, "Events:");
        dropBox->setItems(simulatedTimeTracker->getActionList()); //TODO

        eventDiplsayTexture.loadFromFile("res/eventDisplayBox.png");
        clock = new Clock(473, 26+28);
        timeAndDateTexture.loadFromFile("res/timeAndDateDisplay.png");

        windowBar = new WindowBar(0, 0, *renderWindow, 773, "res/windowBar.png");

        eventButton = new Button("res/eventInactive.png", "res/eventHighlight.png", "res/eventActive.png", "res/eventPressed.png",
                                 798, 43);

        eventWindow = new EventWindow();
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
        windowBar->draw(*renderWindow);
        eventButton->draw(*renderWindow);

        sf::Sprite eventDisplay;
        eventDisplay.setTexture(eventDiplsayTexture);
        eventDisplay.setPosition(463, 374+28);
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
        text.setPosition(474, 383+28);
        renderWindow->draw(text);


        sf::Sprite timeAndDate;
        timeAndDate.setTexture(timeAndDateTexture);
        timeAndDate.setPosition(38, 39+28);
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
        dateText.setPosition(134, 40+28);
        dateText.setFillColor(gray);

        sf::Text timeText(time, font, 19);
        timeText.setPosition(134, 68+28);
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
            stopButton->disable(false);
        } else {
            startButton->disable(false);
            pauseButton->disable(true);
            stopButton->disable(true);
        }

        dropBox->update(*renderWindow);
        startButton->update(*renderWindow);
        pauseButton->update(*renderWindow);
        stopButton->update(*renderWindow);
        windowBar->update(*renderWindow);
        eventButton->update(*renderWindow);

        long time;
        if (simulatedTimeTracker->isThereEventStarted())
            time = simulatedTimeTracker->getCurrentEventDuration();
        else {
            time = ltm->tm_hour * 3600 + ltm->tm_min * 60 + ltm->tm_sec;
        }
        clock->update(*renderWindow, time);
        sf::Event event;
        while (renderWindow->pollEvent(event)) {
            handleEvents(event);
        }

        if (windowBar->isClosePressed()) {
            renderWindow->close();
            eventWindow->close();
        }

        if (windowBar->isCollapsePressed()) {
            windowBar->reset();
            bool screwLinux = setMinimized(renderWindow->getSystemHandle()); //FIXME OS specific
        }

        if (eventButton->isPressed() && !eventWindow->isOpen()) {
            eventWindow->open();
            std::vector<dataPoint> data;
            dataPoint dp("Event", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment");
            data.push_back(dp);
            dataPoint dp1("Event1", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment1");
            data.push_back(dp1);
            dataPoint dp2("Event2", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment2");
            data.push_back(dp2);
            dataPoint dp3("Event3", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment3");
            data.push_back(dp3);
            dataPoint dp4("Event4", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment4");
            data.push_back(dp4);
            dataPoint dp5("Event5", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment5");
            data.push_back(dp5);
            dataPoint dp6("Event6", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment6");
            data.push_back(dp6);
            dataPoint dp7("Event7", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment7");
            data.push_back(dp7);
            dataPoint dp8("Event8", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment8");
            data.push_back(dp8);
            dataPoint dp9("Event9", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment9");
            data.push_back(dp9);
            dataPoint dp10("Event10", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment10");
            data.push_back(dp10);
            dataPoint dp11("Event11", std::chrono::system_clock::now(), std::chrono::system_clock::now(), "Comment11");
            data.push_back(dp11);
            eventWindow->setData(data);
            eventButton->reset();
        } else if (eventButton->isPressed()) {
            eventWindow->close();
            eventButton->reset();
        }
    }

    void handleEvents(sf::Event event) {
        if (event.type == sf::Event::EventType::Closed) {
            renderWindow->close();
        } else {
            if (!windowBar->isDragged()){
                dropBox->handleEvents(*renderWindow, event);
                startButton->handleEvents(*renderWindow, event);
                pauseButton->handleEvents(*renderWindow, event);
                stopButton->handleEvents(*renderWindow, event);
                clock->handleEvents(*renderWindow, event);
                eventButton->handleEvents(*renderWindow, event);
            }
            windowBar->handleEvents(*renderWindow, event);
            renderWindow->setPosition(sf::Vector2i(windowBar->getWinX(), windowBar->getWinY()));
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


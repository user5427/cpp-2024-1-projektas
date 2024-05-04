//
// Created by topto on 2024-05-04.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <valarray>
#include <iostream>
#include "Clock.h"

struct Clock::ClockImpl {
    bool showClock;
    bool disableClock;
    long time, previousTime = -1;
    int hours, minutes, seconds;
    int x, y;

    float secondSmoothener = -1;
    int updates = 0;

    sf::Texture clockTexture;
    sf::Texture hourIndicatorTexture;
    sf::Texture minuteIndicatorTexture;
    sf::Texture secondIndicatorTexture;

    ClockImpl() {
        this->x = x;
        this->y = y;
        showClock = true;
        disableClock = false;
        clockTexture.loadFromFile("res/clock.png");
        hourIndicatorTexture.loadFromFile("res/hourIndicator.png");
        minuteIndicatorTexture.loadFromFile("res/minuteIndicator.png");
        secondIndicatorTexture.loadFromFile("res/secondIndicator.png");

        hourIndicatorTexture.setSmooth(true);
        minuteIndicatorTexture.setSmooth(true);
        secondIndicatorTexture.setSmooth(true);
    }

    ~ClockImpl() {
    }

    void draw(sf::RenderWindow& window) {
        if (showClock) {
            sf::Sprite sprite;
            sprite.setTexture(clockTexture);
            sprite.setPosition(x, y);
            window.draw(sprite);
        }

        sf::Font font;
        font.loadFromFile("res/fonts/inter/Inter-SemiBold.ttf");
        std::string timeString; //= std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
        if (hours < 10)
            timeString += "0";
        timeString += std::to_string(hours) + ":";
        if (minutes < 10)
            timeString += "0";
        timeString += std::to_string(minutes) + ":";
        if (seconds < 10)
            timeString += "0";
        timeString += std::to_string(seconds);

        sf::Text text(timeString, font, 48);
        text.setPosition(x + 54, y + 140);
        window.draw(text);

        float hourRotation = 360.0 / 12.0 * hours;
        float minuteRotation = 360.0 / 60.0 * minutes;
        float secondRotation = 360.0 / 60.0 * (secondSmoothener / 60.0);
        minuteRotation = minuteRotation + secondRotation / 360.0 * (360.0 / 60.0);
        hourRotation = hourRotation + minuteRotation / 360.0 * (360.0 / 12.0);

        sf::Sprite hourIndicator;
        hourIndicator.setTexture(hourIndicatorTexture);
        hourIndicator.setOrigin(6, 6);
        int hourLength = 136+6;
        int xHourStart = 157+6+x;
        int yHourStart = 21+6+y;
        float xHourInd, yHourInd;

        float angle = hourRotation * 3.14159265 / 180;
        xHourInd = xHourStart + hourLength * sin(angle);
        yHourInd = yHourStart - hourLength * (cos(angle)-1);
        hourIndicator.setPosition(xHourInd, yHourInd);
        hourIndicator.setRotation(hourRotation);

        sf::Sprite minuteIndicator;
        minuteIndicator.setTexture(minuteIndicatorTexture);
        minuteIndicator.setOrigin(7, 7);
        int minuteLength = 121+7;
        int xMinuteStart = 156+7+x;
        int yMinuteStart = 34+7+y;
        float xMinuteInd, yMinuteInd;

        angle = minuteRotation * 3.14159265 / 180;
        xMinuteInd = xMinuteStart + minuteLength * sin(angle);
        yMinuteInd = yMinuteStart - minuteLength * (cos(angle)-1);
        minuteIndicator.setPosition(xMinuteInd, yMinuteInd);
        minuteIndicator.setRotation(minuteRotation);

        sf::Sprite secondIndicator;
        secondIndicator.setTexture(secondIndicatorTexture);
        secondIndicator.setOrigin(5, 5);
        int secondLength = 113+5;
        int xSecondStart = 158+5+x;
        int ySecondStart = 46+5+y;
        float xSecondInd, ySecondInd;

        angle = secondRotation * 3.14159265 / 180;
        xSecondInd = xSecondStart + secondLength * sin(angle);
        ySecondInd = ySecondStart - secondLength * (cos(angle)-1);
        secondIndicator.setPosition(xSecondInd, ySecondInd);
        secondIndicator.setRotation(secondRotation);

        window.draw(hourIndicator);
        window.draw(minuteIndicator);
        window.draw(secondIndicator);

    }

    void update(sf::RenderWindow& window) {
    }

    void update(sf::RenderWindow& window, long time) {
        this->time = time;
        hours = time / 3600;
        time = time % 3600;
        minutes = time / 60;
        time = time % 60;
        seconds = time;
        secondSmoothener;

        if (secondSmoothener == -1)
            secondSmoothener = seconds*60;

        if (secondSmoothener/60.0 < seconds)
            secondSmoothener += (seconds*60 - secondSmoothener)/5.0;
        if (secondSmoothener/60.0 - 30 > seconds)
            secondSmoothener -= 60*60;
    }

    void handleEvents(sf::RenderWindow& window, sf::Event event) {
    }

    void show(bool showClock) {
        this->showClock = showClock;
    }

    void disable(bool disableClock) {
        this->disableClock = disableClock;
    }

    void reset() {
        showClock = true;
        disableClock = false;
        time = 0;
        secondSmoothener = -1;
    }


};

Clock::Clock(int x, int y) {
    ptr = new ClockImpl();
    ptr->x = x;
    ptr->y = y;
}

Clock::~Clock() {
    delete ptr;
}

void Clock::draw(sf::RenderWindow& window) {
    ptr->draw(window);
}

void Clock::update(sf::RenderWindow& window) {
    ptr->update(window);
}

void Clock::update(sf::RenderWindow& window, long time) {
    ptr->update(window, time);
}

void Clock::handleEvents(sf::RenderWindow& window, sf::Event event) {
    ptr->handleEvents(window, event);
}

void Clock::show(bool showClock) {
    ptr->show(showClock);
}

void Clock::disable(bool disableClock) {
    ptr->disable(disableClock);
}

void Clock::reset() {
    ptr->reset();
}

// Created by tari9925 on 2024-05-04.
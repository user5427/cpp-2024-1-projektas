//
// Created by topto on 2024-05-04.
//

#ifndef CPP_2024_1_PROJEKTAS_CLOCK_H
#define CPP_2024_1_PROJEKTAS_CLOCK_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "AbstractUIElement.h"

class Clock : public AbstractUIElement{
public:
    Clock(int x, int y);
    ~Clock();
    void draw(sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window, long long time);
    void handleEvents(sf::RenderWindow& window, sf::Event event) override;
    void show(bool showClock) override;
    void disable(bool disableClock) override;
    void reset() override;
private:
    struct ClockImpl;
    ClockImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_CLOCK_H

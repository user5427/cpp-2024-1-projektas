//
// Created by topto on 2024-05-03.
//

#ifndef CPP_2024_1_PROJEKTAS_SLIDER_H
#define CPP_2024_1_PROJEKTAS_SLIDER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "AbstractUIElement.h"

class Slider : public AbstractUIElement {
public:
    Slider(int x, int y, float length, bool vertical);
    ~Slider();
    void draw(sf::RenderWindow& window) override;
    void update(sf::RenderWindow& window) override;
    void handleEvents(sf::RenderWindow& window, sf::Event event) override;
    void show(bool showSlider) override;
    void disable(bool disableSlider) override;
    float getValue();
    /**
     * Reset slider to initial state
     * Set as not active
     */
    void reset() override;
private:
    struct SliderImpl;
    SliderImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_SLIDER_H

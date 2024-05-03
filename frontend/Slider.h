//
// Created by topto on 2024-05-03.
//

#ifndef CPP_2024_1_PROJEKTAS_SLIDER_H
#define CPP_2024_1_PROJEKTAS_SLIDER_H


#include <SFML/Graphics/RenderWindow.hpp>

class Slider {
public:
    Slider(int x, int y, float length, bool vertical);
    ~Slider();
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void handleEvents(sf::RenderWindow& window, sf::Event event);
    void show(bool showSlider);
    void disable(bool disableSlider);
    float getValue();
    /**
     * Reset slider to initial state
     * Set as not active
     */
    void reset();
private:
    struct SliderImpl;
    SliderImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_SLIDER_H

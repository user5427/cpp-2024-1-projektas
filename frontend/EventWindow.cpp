//
// Created by topto on 2024-05-05.
//

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <SFML/System/Thread.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <utility>
#include "EventWindow.h"
#include "Button.h"
#include "../res/logo.c"
#include "Transparent.h"
#include "WindowBar.h"
#include "Slider.h"

struct DisplayPoint2{
    int x, y;
    dataPoint data;
};

struct EventWindow::EventWindowImpl {
    std::vector<DisplayPoint2> displayPoints;
    sf::Thread *thread = nullptr;
    sf::RenderWindow *renderWindow = nullptr;
    sf::Texture windowTexture;

    WindowBar *windowBar = nullptr;

    std::vector<dataPoint> data;

    Slider *slider = nullptr;

    bool openW = false;

    EventWindowImpl() {
    }

    ~EventWindowImpl() {
        close();
    }

    void close() {
        openW = false;
    }

    void open() {
        if (!openW) {
            openW = true;
            start();
        }
    }

    void handleEvents(sf::Event event) {
        if (event.type == sf::Event::EventType::Closed) {
            renderWindow->close();
        } else {
            if (!windowBar->isDragged()) {
                slider->handleEvents(*renderWindow, event);
            }
            windowBar->handleEvents(*renderWindow, event);
        }

        if (windowBar->isClosePressed()) {
            renderWindow->close();
            openW = false;
        }

        if (windowBar->isCollapsePressed()) {
            windowBar->reset();
            bool screwLinux = setMinimized(renderWindow->getSystemHandle()); //FIXME OS specific
        }

        renderWindow->setPosition(sf::Vector2i(windowBar->getWinX(), windowBar->getWinY()));
    }

    void draw() {
        sf::Sprite windowSprite(windowTexture);
        windowSprite.setPosition(0, 0);
        renderWindow->draw(windowSprite);

        sf::Font font;
        font.loadFromFile("res/fonts/inter/Inter-Regular.ttf");
        for (auto & displayPoint : displayPoints) {
            sf::Text text;
            text.setFont(font);
            text.setString(displayPoint.data.getEventName());
            text.setCharacterSize(16);
            text.setPosition(displayPoint.x, displayPoint.y);
            renderWindow->draw(text);

            text.setString(displayPoint.data.getEventComment());
            text.setPosition(displayPoint.x + 128, displayPoint.y);
            renderWindow->draw(text);

            text.setString(displayPoint.data.getEventDate());
            text.setPosition(displayPoint.x + 334, displayPoint.y);
            renderWindow->draw(text);

            text.setString(displayPoint.data.getEventTime());
            text.setPosition(displayPoint.x + 486, displayPoint.y);
            renderWindow->draw(text);

            text.setString(displayPoint.data.getDuration());
            text.setPosition(displayPoint.x + 616, displayPoint.y);
            renderWindow->draw(text);
        }

        windowBar->draw(*renderWindow);
        slider->draw(*renderWindow);

    }

    void update() {
        windowBar->update(*renderWindow);
        slider->update(*renderWindow);

        displayPoints.clear();

        int currentItem = slider->getValue()/100 * (data.size()-16);
        if (currentItem < 0)
            currentItem = 0;

        int j = 0;
        for (int i = currentItem; i < data.size(); ++i) {
            DisplayPoint2 displayPoint{9, 77 + 19*j, data[i]};
            displayPoints.push_back(displayPoint);
            j++;
            if (j > 15)
                break;
        }
    }

    bool isOpen() {
        return openW;
    }

    void setData(const std::vector<dataPoint> data) {
        this->data = data;
    }

    void runner() {
        renderWindow = new sf::RenderWindow(sf::VideoMode(828, 422), "PSP tracker", sf::Style::None);
        renderWindow->setIcon(gimp_image.width, gimp_image.height, gimp_image.pixel_data);
        renderWindow->setFramerateLimit(60);


        sf::Image backgroundImage;
        if (!windowTexture.loadFromFile("res/eventWindow.png") ||
            !backgroundImage.loadFromFile("res/eventWindow.png")) {
            std::cout << "Could not load page windowTexture" << std::endl;
            throw std::runtime_error("Could not load page windowTexture");
        }

        bool setShapeS = setShape(renderWindow->getSystemHandle(), backgroundImage);//FIXME OS specific
        bool setTransparencyS = setTransparency(renderWindow->getSystemHandle(), 255);//FIXME OS specific

        windowBar = new WindowBar(0, 0, *renderWindow, 731, "res/eventBar.png");
        slider = new Slider(786-4, 64+6, 338-12, true);

        while (renderWindow->isOpen() && openW) {
            sf::Event event;
            while (renderWindow->pollEvent(event)) {
                handleEvents(event);
            }
            renderWindow->clear();
            draw();
            update();
            renderWindow->display();
        }

        if (renderWindow->isOpen()) {
            renderWindow->close();
        }
        delete renderWindow;
        delete windowBar;
        delete slider;
    }

    void start() {
        // create a new thread

        thread = new sf::Thread(&EventWindowImpl::runner, this);
        thread->launch();
    }
};

EventWindow::EventWindow() : pimpl(new EventWindowImpl) {
}

EventWindow::~EventWindow() {
    delete pimpl;
}

bool EventWindow::isOpen() {
    return pimpl->isOpen();
}

void EventWindow::setData(std::vector<dataPoint> data) {
    pimpl->setData(data);
}

void EventWindow::close() {
    pimpl->close();
}

void EventWindow::open() {
    pimpl->open();
}

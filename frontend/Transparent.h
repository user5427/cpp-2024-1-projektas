//
// Created by topto on 2024-05-04.
//

#ifndef CPP_2024_1_PROJEKTAS_TRANSPARENT_H
#define CPP_2024_1_PROJEKTAS_TRANSPARENT_H

#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/WindowHandle.hpp>

#if defined (SFML_SYSTEM_WINDOWS)
#include <windows.h>
bool setShape(HWND hWnd, const sf::Image& image);
bool setTransparency(HWND hWnd, unsigned char alpha);
bool setMinimized(HWND hWnd);
#elif defined (SFML_SYSTEM_LINUX)
#include <X11/Xatom.h>
    #include <X11/extensions/shape.h>

    bool setMinimized(Window wnd);
    bool setShape(Window wnd, const sf::Image& image);
    bool setTransparency(Window wnd, unsigned char alpha);

    #undef None // None conflicts with SFML
#elif defined (SFML_SYSTEM_MACOS)
    bool setShape(sf::WindowHandle handle, const sf::Image& image);
    bool setTransparency(sf::WindowHandle handle, unsigned char alpha);
    bool setMinimized(sf::WindowHandle handle);
#else
    bool setShape(sf::WindowHandle handle, const sf::Image& image);
    bool setTransparency(sf::WindowHandle handle, unsigned char alpha);
    bool setMinimized(sf::WindowHandle handle);
#endif


#endif //CPP_2024_1_PROJEKTAS_TRANSPARENT_H

#pragma once
#include "Menu.hpp"
#include <SFML/Graphics.hpp>

class Game
{
private:
    Menu menu;
    sf::RenderWindow window;

public:
    void Run()
    {
        while (window.isOpen())
        {
            menu.PrintMenu(&window);
        }
    }

    Game() : window(sf::VideoMode(1280, 720), "Spadotas")
    {
        window.setFramerateLimit(60);
    }
    ~Game(){};
};
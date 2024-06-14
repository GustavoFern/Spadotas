#pragma once

#include <SFML/Graphics.hpp>

class Window
{
private:
    sf::RenderWindow window;
    sf::Event event;

public:
    Window();
    ~Window();
    void Draw();
    sf::RenderWindow &GetWindow();
};

Window::Window()
    : window(sf::VideoMode(1280, 720), "Player Example")
{
    window.setFramerateLimit(60);
}

Window::~Window()
{
}

void Window::Draw()
{
    window.clear();
    window.display();
}

sf::RenderWindow &Window::GetWindow()
{
    return this->window;
}

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
private:
    sf::RectangleShape button; // Represents the shape of the button
    sf::Texture *texture;      // Pointer to the texture used for the button
    sf::Vector2f position;     // Position of the button
    sf::Vector2f size;         // Size of the button

public:
    Button(sf::Vector2f size, sf::Vector2f position, sf::Texture *texture); // Constructor to initialize the button
    ~Button();                                                              // Destructor to clean up any resources

    void Draw(sf::RenderWindow &window);      // Draws the button on the specified window
    void Update(float deltaTime);             // Updates the button logic
    bool IsPressed(sf::RenderWindow &window); // Checks if the button is pressed
};

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Texture *texture)
    : size(size), position(position), texture(texture)
{
    button.setSize(size);         // Set the size of the button
    button.setPosition(position); // Set the position of the button
    button.setTexture(texture);   // Set the texture of the button
}

Button::~Button() {}

void Button::Draw(sf::RenderWindow &window)
{
    window.draw(button);
}

void Button::Update(float deltaTime)
{
}

bool Button::IsPressed(sf::RenderWindow &window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);                                           // Get the current mouse position relative to the window
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)); // Convert the mouse position to float

    if (button.getGlobalBounds().contains(mousePositionF)) // Check if the mouse is within the bounds of the button
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Check if the left mouse button is pressed
        {
            return true; // Return true if the button is pressed
        }
    }

    return false; // Return false if the button is not pressed
}
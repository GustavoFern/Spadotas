#pragma once
#include <SFML/Graphics.hpp>
#include "button.hpp" 
#include <iostream>

void startFunction() {
    std::cout << "Boton start\n";
}
void exitFunction() {
    std::cout << "Boton salida\n";
}
void controlsFunction() {

    std::cout << "Boton controles\n";

}
void printMenu() {
    sf::RenderWindow menuWindow(sf::VideoMode(1280, 720), "Spadotas Menu");

    // Texturas
    sf::Texture titleTexture;
    titleTexture.loadFromFile("titulo.png");
    sf::Texture menuBackground;
    menuBackground.loadFromFile("fondoMenu.png");
    sf::Texture playButtonTexture;
    playButtonTexture.loadFromFile("playButton.png");
    sf::Texture optionsButtonTexture;
    optionsButtonTexture.loadFromFile("controlsButton.png");
    sf::Texture exitTexture;
    exitTexture.loadFromFile("exitButton.png"); 


    sf::Texture controlsTexture;
    controlsTexture.loadFromFile("controls.png");
    sf::Texture backButtonTexture;
    backButtonTexture.loadFromFile("back.png");


    // Creacion de botones
    Button playButton(sf::Vector2f(280, 80), sf::Vector2f(500, 350), &playButtonTexture);
    Button optionsButton(sf::Vector2f(280, 60), sf::Vector2f(500, 435), &optionsButtonTexture);
    Button exitButton(sf::Vector2f(280, 60), sf::Vector2f(500, 500), &exitTexture);
    Button backButton(sf::Vector2f(700, 130), sf::Vector2f(500, 100), &exitTexture);

    bool inWindow = false; // Add a flag to control the controls window

    while (menuWindow.isOpen()) {
        sf::Event event;
        while (menuWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                menuWindow.close();
        }

        menuWindow.clear();

        // Dibujar fondo
        sf::RectangleShape background(sf::Vector2f(1280, 720));
        background.setTexture(&menuBackground);
        menuWindow.draw(background);

        // Dibujar botones
        playButton.Draw(menuWindow);
        optionsButton.Draw(menuWindow);
        exitButton.Draw(menuWindow);

        // Check for button clicks
        if (playButton.IsPressed(menuWindow)) {
            startFunction();
        }
        if (optionsButton.IsPressed(menuWindow)) {
            controlsFunction();
            inWindow = true; // Set the flag to true when controls button is pressed
        }
        if (exitButton.IsPressed(menuWindow)) {
            exitFunction();
            menuWindow.close();
        }

        // Controls window
        if (inWindow) {
            sf::RectangleShape controls(sf::Vector2f(1280, 720));
            
           
            controls.setTexture(&controlsTexture);

            menuWindow.draw(controls);
            Button backButton(sf::Vector2f(250, 70), sf::Vector2f(500, 140), &backButtonTexture);
            backButton.Draw(menuWindow);

            if (backButton.IsPressed(menuWindow)) {
                inWindow = false; // Set the flag to false when back button is pressed
            }
        }

        menuWindow.display();
    }
}